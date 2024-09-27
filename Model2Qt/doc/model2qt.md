# model2qt.exe usage

## Options and switches

```
Usage: C:\Tools\GoldingsGymStatic\model2qt.exe [options] preserve-case clobber namespace qtclass qtfsm qtsmf etg
model2qt Converts an scxml or class diagram UML file created with Qt Creator into classes, with pre-defined interfaces

Options:
  -?, -h, --help      Displays help on commandline options.
  --help-all          Displays help, including generic Qt options.
  -v, --version       Displays version information.
  -i, --input <file>  Input file

Arguments:
  preserve-case       Preserve case for file names - may be ignored for some input types
  clobber             Overwrite existing files - may be ignored for some input types
  namespace           Use package and component names (if available) as namespaces - may be ignored for some input types
  qtclass             Qt Creator class model diagram to QObjects
  qtfsm               Finite State Machine with QObjects
  qtsmf               Finite State Machine with QStates
  etg                 Create classes for Events, Transitions Guards pattern. Only with "qtsmf" output flag
```

## Namespaces

For class model diagrams, modify the top level 'Name' tag to the namespace, e.g. GoldingsGym::MyLibrary.

For state charts (inc. ETG state charts) modeify the attributes 'name' tag to add the namespace onto the state machine name with a hyphen delimiter, e.g. MyFsm-GoldingsGym::MyFsm

### Class model diagram

![class_model.png](class_model.png)

### State chart (simple pattern)

![state_chart.png](state_chart.png)

### State chart (events, transitions and guards pattern)

![etg_state_chart.png](etg_state_chart.png)

