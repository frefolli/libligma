project('libligma', 'cpp', version: 'master')

# Features

# Infos
THE_ASSEMBLER = 'GAS'
THE_BUILDER = 'Ninja'

THE_COMPILER = '@0@ @1@'.format(
  meson.get_compiler('cpp').get_id(),
  meson.get_compiler('cpp').version()
)

THE_VERSION='master'
THE_BRANCH='master'
THE_OS = '@0@ @1@'.format(
  build_machine.system(),
  build_machine.cpu()
)

THE_PROJECT = 'LibLigma'

add_project_arguments('-DTHE_ASSEMBLER="@0@"'.format(THE_ASSEMBLER), language : 'cpp')
add_project_arguments('-DTHE_COMPILER="@0@"'.format(THE_COMPILER), language : 'cpp')
add_project_arguments('-DTHE_BUILDER="@0@"'.format(THE_BUILDER), language : 'cpp')
add_project_arguments('-DTHE_OS="@0@"'.format(THE_OS), language : 'cpp')
add_project_arguments('-DTHE_BRANCH="@0@"'.format(THE_BRANCH), language : 'cpp')
add_project_arguments('-DTHE_VERSION="@0@"'.format(THE_VERSION), language : 'cpp')
add_project_arguments('-DTHE_PROJECT="@0@"'.format(THE_PROJECT), language : 'cpp')

libutils_dep = dependency(
  'libutils',
  fallback: ['libutils', 'libutils_dep'],
  version: 'master',
)

libyaml_dep = dependency('yaml-cpp')
include = include_directories('include')

libligma = library('libligma', [
    'src/libligma/document.cc',
    'src/libligma/yaml_document.cc',
    'src/libligma/symbol.cc',
    'src/libligma/production.cc',
    'src/libligma/asset.cc',
    'src/libligma/first_set.cc',
    'src/libligma/follow_set.cc',
  ], include_directories : include,
  dependencies: [libyaml_dep, libutils_dep])

main = executable('main.exe', [
    'src/main.cc',
  ], include_directories : include,
  link_with: [libligma])

libligma_dep = declare_dependency(
  include_directories : include,
  link_with : libligma)
