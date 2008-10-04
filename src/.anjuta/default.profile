<?xml version="1.0"?>
<anjuta>
    <plugin name="Debugger" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-debug-manager:DebugManagerPlugin"/>
    </plugin>
    <plugin name="Valgrind Plugin" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-valgrind:AnjutaValgrindPlugin"/>
    </plugin>
    <plugin name="Subversion" mandatory="no">
        <require group="Anjuta Plugin"
                 attribute="Location"
                 value="anjuta-subversion:Subversion"/>
    </plugin>
</anjuta>
