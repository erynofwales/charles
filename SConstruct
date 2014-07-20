# SConstruct
# vim: set ft=python:
# Eryn Wells <eryn@erynwells.me>


#
# DEFAULT CONFIGURATION VALUES
#

# Settings for the default toolchain binaries. Setting these overrides the
# defaults, provided your the given binary exists.
CC = None
CXX = None
AS = None
LINK = 'clang++'

CCFLAGS = ['-Wall', '-Wextra', '-pedantic']


#
# BUILD STUFF BELOW HERE
#

import os
import os.path
import sys
import SCons.Errors


def which(program):
    def is_executable(path):
        return os.path.exists(path) and os.access(path, os.X_OK)

    path, name = os.path.split(program)
    if path:
        if is_executable(program):
            return program
    else:
        pathext = [''] + os.environ.get('PATHEXT', '').split(os.pathsep)
        for path in os.environ.get('PATH', '').split(os.pathsep):
            exe = os.path.join(path, program)
            for ext in pathext:
                candidate = exe + ext
                if is_executable(candidate):
                    return candidate
    return None


def get_bool_argument(arg):
    try:
        return bool(int(arg))
    except ValueError:
        pass
    if arg in ('False', 'FALSE', 'false', ''):
        return False
    return True


def set_toolchain_binary(env, var, user_binary, binaries=()):
    if user_binary and which(user_binary):
        env[var] = user_binary
        return
    for c in binaries:
        if which(c):
            env[var] = c
            break

common_env = Environment()
set_toolchain_binary(common_env, 'CC', CC, ('clang', 'gcc'))
set_toolchain_binary(common_env, 'CXX', CXX, ('clang++', 'g++'))
set_toolchain_binary(common_env, 'AS', AS)
set_toolchain_binary(common_env, 'LINK', LINK)


def verbose_build_cmds():
    def generate_comstr(action):
        return '{:>25}: $TARGET'.format(action)
    common_env['ARCOMSTR'] = generate_comstr('Archiving')
    common_env['ASCOMSTR'] = generate_comstr('Assembling')
    common_env['ASPPCOMSTR'] = generate_comstr('Assembling')
    common_env['CCCOMSTR'] = generate_comstr('Building (C)')
    common_env['CXXCOMSTR'] = generate_comstr('Building (C++)')
    common_env['LINKCOMSTR'] = generate_comstr('Linking')
    common_env['RANLIBCOMSTR'] = generate_comstr('Indexing')
    common_env['SHCCCOMSTR'] = generate_comstr('Building (C, Shared)')
    common_env['SHCXXCOMSTR'] = generate_comstr('Building (C++, Shared)')
    common_env['SHLINKCOMSTR'] = generate_comstr('Linking (Shared)')


def succinct_build_cmds():
    def generate_comstr(action):
        return '  [{:^6}] $TARGET'.format(action)
    common_env['ARCOMSTR'] = generate_comstr('AR')
    common_env['ASCOMSTR'] = generate_comstr('AS')
    common_env['ASPPCOMSTR'] = generate_comstr('AS')
    common_env['CCCOMSTR'] = generate_comstr('CC')
    common_env['CXXCOMSTR'] = generate_comstr('CXX')
    common_env['LINKCOMSTR'] = generate_comstr('LINK')
    common_env['RANLIBCOMSTR'] = generate_comstr('RANLIB')
    common_env['SHCCCOMSTR'] = generate_comstr('SHCC')
    common_env['SHCXXCOMSTR'] = generate_comstr('SHCXX')
    common_env['SHLINKCOMSTR'] = generate_comstr('SHLINK')


BUILD_CMDS = get_bool_argument(ARGUMENTS.get('BUILD_CMDS', False))
if not BUILD_CMDS:
    verbose_build_cmds()

# Separate environment for building libraries because they often don't use the
# same CCFLAGS I do.
lib_env = common_env.Clone()

common_env.Append(CCFLAGS=CCFLAGS)
common_env.Append(CFLAGS=['-std=c99'])
common_env.Append(CXXFLAGS=['-std=c++11'])

# Add color error messages for clang
if sys.stdout.isatty():
    if 'clang' in common_env['CC'] or 'clang' in common_env['CXX']:
        common_env.Append(CCFLAGS=['-fcolor-diagnostics'])

BUILD_DIR = Dir('#build')
LIB_DIR = Dir('#lib')
SRC_DIR = Dir('#src')
TEST_DIR = Dir('#test')


def create_env(name, appends=None):
    output_dir = BUILD_DIR.Dir(name)
    env = common_env.Clone()
    # Standard env extensions.
    env.Append(CPPPATH=[SRC_DIR])
    # Custom env stuff.
    env['__name'] = name
    if appends:
        for k, v in appends.iteritems():
            if k.startswith('='):
                env[k[1:]] = v
            else:
                env.Append(**{k: v})
    return env


def do_sconscript(env, build_env, src_dir, out_dir):
    sconscript = src_dir.File('SConscript')
    print 'Reading {}'.format(sconscript)
    # Swapping env and build_env here is a bit wacky. Doing so means that env is
    # always the Environment that the SConscript should be building with, while
    # build_env is the Environment we're using to put everything together.
    env.SConscript(sconscript,
                   {'env': build_env, 'build_env': env},
                   variant_dir=out_dir,
                   duplicate=0)


debug_env = create_env('debug', {
    'CPPDEFINES': ['DEBUG', 'NRELEASE'],
    'CCFLAGS': ['-O0', '-g'],
})

beta_env = create_env('beta', {
    'CPPDEFINES': ['DEBUG', 'NRELEASE'],
    'CCFLAGS': ['-O3', '-g'],
})

release_env = create_env('release', {
    'CPPDEFINES': ['NDEBUG', 'RELEASE'],
    'CCFLAGS': ['-O3']
})


modes = {
    'debug': debug_env,
    'beta': beta_env,
    'release': release_env,
}

mode = ARGUMENTS.get('MODE', None)
build_modes = []
if mode:
    # If MODE=foo is specified, build only that mode.
    build_modes.append(mode)
else:
    build_modes = ['debug']

for mode in build_modes:
    try:
        env = modes[mode]
    except KeyError:
        print 'Skipping invalid mode: {}'.format(mode)
        break

    out_dir = BUILD_DIR.Dir(env['__name'])

    # Process all lib dirs.
    for lib in os.listdir(LIB_DIR.abspath):
        lib_out_dir = out_dir.Dir('lib').Dir(lib)
        do_sconscript(env, lib_env, LIB_DIR.Dir(lib), lib_out_dir)
        env.Append(LIBPATH=[lib_out_dir])

    # Get test binaries.
    do_sconscript(env, env, TEST_DIR, out_dir.Dir('test'))

    # Get source files.
    src_out_dir = out_dir.Dir('src')
    do_sconscript(env, env, SRC_DIR, src_out_dir)
    env.Append(LIBPATH=[src_out_dir])
