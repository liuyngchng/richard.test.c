Waf: Entering directory `/home/ns-allinone-3.30.1/ns-3.30.1/build'
[1908/2032] Compiling build/src/internet/bindings/ns3module.cc
[1913/2032] Compiling build/src/lte/bindings/ns3module.cc
g++: internal compiler error: Killed (program cc1plus)
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-7/README.Bugs> for instructions.

Waf: Leaving directory `/home/ns-allinone-3.30.1/ns-3.30.1/build'
Build failed
 -> task in 'ns3module_lte' failed with exit status 4 (run with -v to display more information)
Traceback (most recent call last):
  File "build.py", line 175, in <module>
    sys.exit(main(sys.argv))
  File "build.py", line 166, in main
    build_ns3(config, build_examples, build_tests, args, build_options)
  File "build.py", line 86, in build_ns3
    run_command([sys.executable, "waf", "build"] + build_options)
  File "/home/ns-allinone-3.30.1/util.py", line 25, in run_command
    raise CommandError("Command %r exited with code %i" % (argv, retval))
util.CommandError: Command ['/usr/bin/python3', 'waf', 'build'] exited with code 1
root@279d743cead4:/home/ns-allinone-3.30.1# `
