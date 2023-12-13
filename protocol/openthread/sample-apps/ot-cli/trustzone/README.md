# TrustZone OpenThread CLI (Workspace and Non-Secure Application)

The Simplicity IDE uses the `ot-cli-ftd-tz` and `ot-cli-mtd-tz` workspaces to create the 
secure and non-secure applications for the TrustZone OpenThread CLI example solutions.
Additionally, these workspaces include the `bootloader-storage-internal-single` bootloader
application, which will allow the following post-build actions to process:

* Combine the secure and non-secure binaries into an `app-only` image.
* Combine the bootloader binary with the previous artifacts into a `full` image.
* Generate a GBL file of the `app-only` image to be used for firmware upgrades.

## Getting Started

Generating and building the entire workspace will build the constituent projects and produce
the post-build artifacts mentioned above. From the `artifacts/` directory, flash either the
`full` image, or the `app-only` image and a separate bootloader binary, and the OpenThread CLI
should be present when interacting with the application terminal.

See the application README file for details on how to use the OpenThread CLI.

## Troubleshooting

The bootloader, secure app, and non-secure app need to have coordinated flash and ram memory
segments defined which don't overlap and aren't too small for the firmware. If running into issues,
particularly when installing additional components, it is recommended to use the
Simplicity Memory Editor tool to ensure that appropriate regions are defined.

## Additional Resources

[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)
