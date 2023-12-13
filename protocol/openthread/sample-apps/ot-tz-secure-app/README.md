# OpenThread TrustZone Secure Application

The ot-tz-secure-application example application is a TrustZone-secure application that performs
PSA operations for OpenThread TrustZone-non-secure projects.

The following items are needed to incorporate this example secure app into a TrustZone solution:

* A TrustZone non-secure application
* A TrustZone workspace

## Defining a Non-Secure Application

A TrustZone non-secure application is similar to any TrustZone-unaware example applications 
with a few additional properties:

* Includes the `trustzone_nonsecure` and `tz_secure_key_library` components.
* Defines a template contribution for flash start/size and ram start/size, 
    which can be modified using the Memory Editor tool.
* Imports the config files from this TrustZone secure application.
* Uses a `tz_nonsecure_application` (or similar) postbuild profile.

## Defining a TrustZone Workspace

To pair this secure app with a non-secure app, a workspace is necessary for managing the reserved 
memory requirements of each project and converting the project artifacts into a combined TrustZone
executable.

The following properties are needed to use this secure application in a TrustZone workspace:

* Includes the path to this project file.
* Adds the `id:` tag which is listed under the `import:` section of the non-secure application.
* Includes the path to a non-secure application.
* Adds the `id:` tag of `ot-tz-nonsecure-application` to be imported by this secure application.
* Uses a `tz_application` (or similar) postbuild profile.

Optionally, a bootloader project can be included with the workspace for convenience.

## Resources

[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)
