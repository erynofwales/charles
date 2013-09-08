# SConstruct
# vim: set ft=python:
#
# Toplevel Scons build script for the Charles project.
#
# Eryn Wells <eryn@erynwells.me>


#
# DEFAULT CONFIGURATION VALUES
#

# Enabling debugging does the following things:
#   1. Turns on debugging symbols
#   2. Turns off all optimization
#   3. Sets the DEBUG define
DEBUG = True

# Show build commands ("cc [args] -o [out] [file], etc"). If this is False, show
# some nice messages for each step of the build.
BUILD_CMDS = False

# Library directories. Where should scons look for .a files during linking?
lib_directories = Split("""
""")

# Source directories. New directories should contain a SConscript file and be
# added here.
source_directories = lib_directories + Split("""
        #src
        #test
""")

# Include directories. Where should scons look for headers during preprocessing
# and compiling?
include_directories = Split("""
        #src
""")
 

#
# BUILD STUFF BELOW HERE
#

import os.path


env = Environment(CC='clang',
                  CFLAGS='-Wall -fcolor-diagnostics',
                  CPPPATH=include_directories,
                  LIBS='png',
                  LIBPATH=lib_directories)


# Handle command line variables
DEBUG = bool(int(ARGUMENTS.get('DEBUG', DEBUG)))
if DEBUG:
    env.Append(CFLAGS=' -g -O0')
    env.Append(CPPDEFINES=['DEBUG'])
else:
    env.Append(CFLAGS=' -O2')

BUILD_CMDS = bool(int(ARGUMENTS.get('BUILD_CMDS', BUILD_CMDS)))
if not BUILD_CMDS:
    def generate_comstr(action):
        return '%12s: $TARGET' % (action,)
    env['CCCOMSTR'] = generate_comstr('Building'),
    env['LINKCOMSTR'] = generate_comstr('Linking'),
    env['ARCOMSTR'] = generate_comstr('Archiving'),
    env['RANLIBCOMSTR'] = generate_comstr('Indexing')


# Build charles
src_dir = Dir('#src')
charles_lib = env.SConscript(os.path.join(src_dir.path, 'SConscript'),
                             exports='env',
                             variant_dir=os.path.join('build', src_dir.path),
                             duplicate=0)
charles = env.Program(os.path.join('build', 'charles'), charles_lib)

# Build test
test_dir = Dir('#test')
test_lib = env.SConscript(os.path.join(test_dir.path, 'SConscript'),
                          exports='env',
                          variant_dir=os.path.join('build', test_dir.path),
                          duplicate=0)
test_charles = env.Program(os.path.join('build', 'test_charles'), [charles_lib, test_lib])

env.Alias('charles', charles)
env.Alias('test', test_charles)
env.Default(charles)
