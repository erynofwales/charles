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
                  LINKFLAGS='',
                  LIBPATH=lib_directories)


# Handle command line variables
DEBUG = bool(int(ARGUMENTS.get('DEBUG', DEBUG)))
if DEBUG:
    env.Append(CXXFLAGS=' -g -O0')
    env.Append(CPPDEFINES=['DEBUG'])
else:
    env.Append(CXXFLAGS=' -O2')

BUILD_CMDS = bool(int(ARGUMENTS.get('BUILD_CMDS', BUILD_CMDS)))
if not BUILD_CMDS:
    def generate_comstr(action):
        return '%12s: $TARGET' % (action,)
    env['CCCOMSTR'] = generate_comstr('Building'),
    env['LINKCOMSTR'] = generate_comstr('Linking'),
    env['ARCOMSTR'] = generate_comstr('Archiving'),
    env['RANLIBCOMSTR'] = generate_comstr('Indexing')


# Build source subdirectories
env.SConscript([os.path.join(dir, 'SConscript') for dir in source_directories],
               exports='env')

Default('charles')
