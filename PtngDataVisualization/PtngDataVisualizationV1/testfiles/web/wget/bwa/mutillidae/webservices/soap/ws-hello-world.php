
		<html><head><title>NuSOAP: hellowsdl</title>
		<style type="text/css">
		    body    { font-family: arial; color: #000000; background-color: #ffffff; margin: 0px 0px 0px 0px; }
		    p       { font-family: arial; color: #000000; margin-top: 0px; margin-bottom: 12px; }
		    pre { background-color: silver; padding: 5px; font-family: Courier New; font-size: x-small; color: #000000;}
		    ul      { margin-top: 10px; margin-left: 20px; }
		    li      { list-style-type: none; margin-top: 10px; color: #000000; }
		    .content{
			margin-left: 0px; padding-bottom: 2em; }
		    .nav {
			padding-top: 10px; padding-bottom: 10px; padding-left: 15px; font-size: .70em;
			margin-top: 10px; margin-left: 0px; color: #000000;
			background-color: #ccccff; width: 20%; margin-left: 20px; margin-top: 20px; }
		    .title {
			font-family: arial; font-size: 26px; color: #ffffff;
			background-color: #999999; width: 100%;
			margin-left: 0px; margin-right: 0px;
			padding-top: 10px; padding-bottom: 10px;}
		    .hidden {
			position: absolute; visibility: hidden; z-index: 200; left: 250px; top: 100px;
			font-family: arial; overflow: hidden; width: 600;
			padding: 20px; font-size: 10px; background-color: #999999;
			layer-background-color:#FFFFFF; }
		    a,a:active  { color: charcoal; font-weight: bold; }
		    a:visited   { color: #666666; font-weight: bold; }
		    a:hover     { color: cc3300; font-weight: bold; }
		</style>
		<script language="JavaScript" type="text/javascript">
		<!--
		// POP-UP CAPTIONS...
		function lib_bwcheck(){ //Browsercheck (needed)
		    this.ver=navigator.appVersion
		    this.agent=navigator.userAgent
		    this.dom=document.getElementById?1:0
		    this.opera5=this.agent.indexOf("Opera 5")>-1
		    this.ie5=(this.ver.indexOf("MSIE 5")>-1 && this.dom && !this.opera5)?1:0;
		    this.ie6=(this.ver.indexOf("MSIE 6")>-1 && this.dom && !this.opera5)?1:0;
		    this.ie4=(document.all && !this.dom && !this.opera5)?1:0;
		    this.ie=this.ie4||this.ie5||this.ie6
		    this.mac=this.agent.indexOf("Mac")>-1
		    this.ns6=(this.dom && parseInt(this.ver) >= 5) ?1:0;
		    this.ns4=(document.layers && !this.dom)?1:0;
		    this.bw=(this.ie6 || this.ie5 || this.ie4 || this.ns4 || this.ns6 || this.opera5)
		    return this
		}
		var bw = new lib_bwcheck()
		//Makes crossbrowser object.
		function makeObj(obj){
		    this.evnt=bw.dom? document.getElementById(obj):bw.ie4?document.all[obj]:bw.ns4?document.layers[obj]:0;
		    if(!this.evnt) return false
		    this.css=bw.dom||bw.ie4?this.evnt.style:bw.ns4?this.evnt:0;
		    this.wref=bw.dom||bw.ie4?this.evnt:bw.ns4?this.css.document:0;
		    this.writeIt=b_writeIt;
		    return this
		}
		// A unit of measure that will be added when setting the position of a layer.
		//var px = bw.ns4||window.opera?"":"px";
		function b_writeIt(text){
		    if (bw.ns4){this.wref.write(text);this.wref.close()}
		    else this.wref.innerHTML = text
		}
		//Shows the messages
		var oDesc;
		function popup(divid){
		    if(oDesc = new makeObj(divid)){
			oDesc.css.visibility = "visible"
		    }
		}
		function popout(){ // Hides message
		    if(oDesc) oDesc.css.visibility = "hidden"
		}
		//-->
		</script>
		</head>
		<body>
		<div class=content>
			<br><br>
			<div class=title>hellowsdl</div>
			<div class=nav>
				<p>View the <a href="/mutillidae/webservices/soap/ws-hello-world.php?wsdl">WSDL</a> for the service.
				Click on an operation name to view it&apos;s details.</p>
				<ul><li><a href='#' onclick="popout();popup('hello')">hello</a></li><div id='hello' class='hidden'>
				    <a href='#' onclick='popout()'><font color='#ffffff'>Close</font></a><br><br><font color='white'>Name:</font> hello<br><font color='white'>Binding:</font> hellowsdlBinding<br><font color='white'>Endpoint:</font> http://bwa/mutillidae/webservices/soap/ws-hello-world.php<br><font color='white'>SoapAction:</font> urn:hellowsdl#hello<br><font color='white'>Style:</font> rpc<br><font color='white'>Input:</font><br>&nbsp;&nbsp;use: encoded<br>&nbsp;&nbsp;namespace: urn:hellowsdl<br>&nbsp;&nbsp;encodingStyle: http://schemas.xmlsoap.org/soap/encoding/<br>&nbsp;&nbsp;message: helloRequest<br>&nbsp;&nbsp;parts:<br>&nbsp;&nbsp;&nbsp;&nbsp;name: xsd:string<br><font color='white'>Output:</font><br>&nbsp;&nbsp;use: encoded<br>&nbsp;&nbsp;namespace: urn:hellowsdl<br>&nbsp;&nbsp;encodingStyle: http://schemas.xmlsoap.org/soap/encoding/<br>&nbsp;&nbsp;message: helloResponse<br>&nbsp;&nbsp;parts:<br>&nbsp;&nbsp;&nbsp;&nbsp;return: xsd:string<br><font color='white'>Namespace:</font> urn:hellowsdl<br><font color='white'>Transport:</font> http://schemas.xmlsoap.org/soap/http<br><font color='white'>Documentation:</font> Says hello to the caller<br></div>
				<ul>
			</div>
		</div></body></html>
