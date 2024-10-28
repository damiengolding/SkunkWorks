#include "ptngidentifier.hpp"

namespace GoldingsGym::Ptng {
PtngIdentifier::PtngIdentifier(QObject *parent)
    : QObject{parent}
{

}

PtngIdentifier::~PtngIdentifier()
{

}

PtngEnums::SupportedInputType PtngIdentifier::checkFile(const QString &file)
{
    PtngEnums::SupportedInputType ret = PtngEnums::NUM_SUPPORTED_INPUT_TYPES;
    QDomDocument doc("input");
    QFile f(file);
    if( !f.open(QIODevice::ReadOnly) ){
        return(ret);
    }
    // Special case - image
    QImage image;
    if(image.load(file)  ){
        return( PtngEnums::IMAGE );
    }
    if(doc.setContent(&f)){
        f.close();
        ret = checkXmlFile(file);
        return(ret);
    }
    else{
        f.close();
        ret = checkTextFile(file);
        return(ret);
    }
    return(ret);
}

PtngEnums::SupportedInputType PtngIdentifier::checkXmlFile(const QString &file)
{
    PtngEnums::SupportedInputType ret = PtngEnums::NUM_SUPPORTED_INPUT_TYPES;
    QScopedPointer<QDomDocument> doc(new QDomDocument("input"));
    QScopedPointer<QFile> f(new QFile(file));
    f->open(QIODevice::ReadOnly);
    doc->setContent(f.data());
    QDomElement rootElem = doc->documentElement();

    if( rootElem.hasAttribute("scanner") ){
        if( rootElem.attribute("scanner").toLower() == "nmap" ){
            if( rootElem.attribute("args").contains("-sS") ||
                    rootElem.attribute("args").contains("-sU") ||
                    rootElem.attribute("args").contains("-sT") ||
                    rootElem.attribute("args").contains("-sA") ||
                    rootElem.attribute("args").contains("-sF") ||
                    rootElem.attribute("args").contains("-sN") ||
                    rootElem.attribute("args").contains("-sX")
                    ){
                ret = PtngEnums::NMAP;
                return(ret);
            }
            else if( rootElem.attribute("args").contains("dns-zone-transfer") ){
                ret = PtngEnums::AXFR_NMAP;
                return(ret);
            }
            else{
                return(ret);
            }
        }
        else if(rootElem.attribute("scanner").toLower() == "masscan"){
            ret = PtngEnums::MASSCAN;
            return(ret);
        }
        else{
            return(ret);
        }
    }
    else if( rootElem.tagName().toLower() == "directedgraph" ){
        if( !rootElem.hasAttribute("Title") ){
            return(PtngEnums::NUM_SUPPORTED_INPUT_TYPES);
        }
        if( rootElem.attribute("Title") == "NmapDGML" || rootElem.attribute("Title") == "NessusDGML" ){
            ret = PtngEnums::DGML;
            return(ret);
        }
        else{
            return(PtngEnums::NUM_SUPPORTED_INPUT_TYPES);
        }
    }
    else if( rootElem.tagName().toLower() == "records" ){
        ret = PtngEnums::AXFR_DNS_RECON;
        return(ret);
    }
    else if( rootElem.tagName().toLower() == "niktoscans" ){
        ret = PtngEnums::NIKTO;
        return(ret);
    }
    else if( rootElem.tagName() == "report" && rootElem.attribute("type").toLower() == "security" ){
        ret = PtngEnums::WAPITI;
        return(ret);
    }
    else if( rootElem.tagName() == "report" &&
             rootElem.hasAttribute("id") &&
             rootElem.hasAttribute("format_id") &&
             rootElem.hasAttribute("content_type")
             ){
        ret = PtngEnums::OPENVAS;
        return(ret);
    }
    else if( rootElem.tagName() == "document" && rootElem.attribute("title").toLower() == "sslscan results" ){
        ret = PtngEnums::SSL_SCAN;
        return(ret);
    }
    else if( rootElem.tagName().toLower().contains(("metasploit"))){
        ret = PtngEnums::METASPLOIT;
        return(ret);
    }
    else if( rootElem.tagName().toLower() == "owaspzapreport" ){
        ret = PtngEnums::OWASP_ZAP;
        return(ret);
    }
    else if( rootElem.tagName().toLower().startsWith("nessusclientdata" )){
        ret = PtngEnums::NESSUS;
        return(ret);
    }
    return(ret);
}

PtngEnums::SupportedInputType PtngIdentifier::checkTextFile(const QString &file)
{
    PtngEnums::SupportedInputType ret = PtngEnums::NUM_SUPPORTED_INPUT_TYPES;
    QScopedPointer<QFile> f(new QFile(file));
    f->open(QIODevice::ReadOnly);
    QString firstLine ,secondLine;
    QStringList lines;
    QTextStream stream(f.data());
    while( !stream.atEnd() ){
        QString line = stream.readLine();
        if( line.isEmpty() || line.startsWith("> ls") ){ // for dig and nslookup
            continue;
        }
        lines.append(line);
    }
    // When it is sufficient and realistic to rely on file extensions - so far this is ony really code files
    QFileInfo fileInfo( file );
    QString extension = fileInfo.suffix().toLower();
    if( extension == "c"
            || extension == "cpp"
            || extension == "css"
            || extension == "h"
            || extension == "hpp"
            || extension == "html"
            || extension == "js"
            || extension == "json"
            || extension == "md"
            || extension == "pl"
            || extension == "ps1"
            || extension == "py"
            || extension == "rb"
            || extension == "sh"
            || extension == "sql"
            || extension == "vbs"
            || extension == "xml"
            || extension == "yaml"
            ){
        return(PtngEnums::CODE);
    }
    else if( extension == "png"
             || extension == "jpg"
             || extension == "jpeg"
             || extension == "gif"
             || extension == "bmp"
             ){
        return( PtngEnums::IMAGE );
    }

    // When it is necessary to open up the file and inspect teh file's contents
    if( lines.at(0).startsWith("ns:",Qt::CaseInsensitive) && lines.at(1).toLower().startsWith("soa:") ){
        ret = PtngEnums::AXFR_FIERCE;
        return(ret);
    }
    else if( lines.at(0).startsWith("trying",Qt::CaseInsensitive) && lines.at(1).toLower().startsWith("using domain server") ){
        ret = PtngEnums::AXFR_HOST;
        return(ret);
    }
    else if( lines.at(0).startsWith("server:",Qt::CaseInsensitive) && lines.at(1).toLower().startsWith("address:") ){
        ret =PtngEnums:: PtngEnums::AXFR_NS_LIN;
        return(ret);
    }
    else if( lines.at(0).startsWith("[[",Qt::CaseInsensitive) && lines.at(0).toLower().endsWith("]]") ){
        ret = PtngEnums::AXFR_NS_WIN;
        return(ret);
    }
    else if( lines.at(0).startsWith("; <<>> dig",Qt::CaseInsensitive) && lines.at(0).toLower().endsWith("axfr") ){
        ret = PtngEnums::AXFR_DIG;
        return(ret);
    }
    else if( lines.at(0).startsWith("[nessus_hsh]",Qt::CaseInsensitive)){
        ret = PtngEnums::NESSUS_HSH;
        return(ret);
    }
    else if( lines.at(0).count(QLatin1Char(':')) == 6 ){
        ret = PtngEnums::HASHES;
        return(ret);
    }
    else if( lines.at(0).startsWith("interface",Qt::CaseInsensitive) &&  lines.at(1).toLower().startsWith("starting arp-scan")){
        ret = PtngEnums::ARPSCAN;
        return(ret);
    }
    else if( lines.at(0).count(QLatin1Char(':')) == 9 ){
        QString ipAddress = lines.at(0).split(":").at(0);
        if( ipAddress.count(QLatin1Char('.')) == 3 ){
            ret = PtngEnums::NBTSCAN;
            return(ret);
        }
    }
    else if( lines.at(0).contains( QLatin1Char(',') ) ){
        int commaCount = lines.at(0).count( QLatin1Char(',')  );
        for( auto line : lines ){
            if( line.count( QLatin1Char(',')) != commaCount ){
                break;
            }
        }
        ret = PtngEnums::CSV;
        return(ret);
    }
    else if( lines.at(0).contains( QLatin1Char('\t') ) ){
        int tabCount = lines.at(0).count( QLatin1Char('\t')  );
        for( auto line : lines ){
            if( line.count( QLatin1Char('\t')) != tabCount ){
                break;
            }
        }
        ret = PtngEnums::TSV;
        return(ret);
    }

    return(ret);
}
} // End of namespace GoldingsGym::Ptng
