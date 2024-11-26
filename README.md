# ch32l103evt with gcc and makefile support

This is pre-converted ch32l103 firmware library with gcc and makefile support from WCH official CH32L103EVT.ZIP. 

It is converted by '[ch32v_evt_makefile_gcc_project_template](https://github.com/cjacker/ch32v_evt_makefile_gcc_project_template)'

This firmware library support below parts from WCH:

- ch32l103f8p6
- ch32l103f8u6
- ch32l103g8r6
- ch32l103k8u6
- ch32l103c8t6

The default part is set to 'ch32l103c8t6', you can change it with `./setpart.sh <part>`. the corresponding 'Link.ld' will update automatically from the template.

The default 'User' codes is 'GPIO_Toggle' from the EVT example, all examples shipped in original EVT package provided in 'Examples' dir.

To build the project, type `make`.

## Note

Please refer to [opensource-toolchain-ch32v tutorial](https://github.com/cjacker/opensource-toolchain-ch32v) for more info.

And you must use [this latest WCH OpenOCD](https://github.com/cjacker/wch-openocd).

