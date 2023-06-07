# What is a migration code block and how to use them

Migration code blocks are introduced when there is an incompatible code change between two major
releases of the GSDK. This happens when there is a change in the file structure. This change necessitates
a migration block. Then the migration code blocks transform the relevant data from the older format
to the newer format. Such changes are introduced only on the minor GSDK releases and never on any patch changes.
These migration code blocks are relevant only when the user is on an older GSDK version and would like to port 
or migrate an existing code base to the newer GSDK version.

### Migration Code 

This is the code that actually does the transformation or migration from the older file version to the newer 
file version. This is usually implemented in a file by name `<module_name>_nvm.c` . This file has a function 
by name `<module_name>_migrate` or `<module_name>_Migrate`. In the migrate function, the code that does the actual 
transformation is wrapped in  a `#ifdef ... #endif` guard. The define used is of the form `ZW_MIGRATION_TO_<MAJOR>_<MINOR>` 
where the MAJOR and MINOR are the GSDK versions. 

Sample migration function

```c
cc_door_lock_migrate(void)
{
  #ifdef ZW_MIGRATION_TO_7_19
  ...
  ...
  #endif
}
```


### Usage

As mentioned in the in the previous section, the migration code blocks are installed by default. In the Studio UI, these 
are usually found under the Software Components > Z--Wave > Migration section in the project configuration. Each of the 
component is the shown is the migration code released in a specific GSDK version. If a user is on a later GSDK version, then 
an older component is redundant and can be safely uninstalled. If the user is on the latest GSDK version, all the older components
can be uninstalled to save some flash and ram. If the user is on an older GSDK version and would like to build the project with the 
latest GSDK, then the user should select all those components that are greater than the GSDK version at the time of the project creation.
This ensures that any incompatible file structures are automatically transformed to the latest GSDK version. 
