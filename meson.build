project(
  'gamejam_factory',
  'cpp',
  version: '0.0.1',
  meson_version: '>=0.50',
  default_options: ['warning_level=3', 'cpp_std=c++23'],
)

libjamfactory_proj = subproject('libjamfactory')
libjamfactory_dep = libjamfactory_proj.get_variable('libjamfactory_dep')

sfml_dep = dependency('sfml-all')
spdlog_dep = dependency('spdlog')

dependencies = [libjamfactory_dep, sfml_dep, spdlog_dep]
cpp_pch = ['pch/pch.hpp', 'pch/pch.cpp']

executable(
  'jamfactory-client',
  'client/src/main.cpp',
  install: true,
  dependencies: dependencies,
  cpp_pch: cpp_pch,
)

executable(
  'jamfactory-server',
  'server/src/main.cpp',
  install: true,
  dependencies: dependencies,
  cpp_pch: cpp_pch,
)
