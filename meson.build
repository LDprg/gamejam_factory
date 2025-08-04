project(
  'gamejam_factory',
  'cpp',
  version: '0.1',
  meson_version: '>= 1.3.0',
  default_options: ['warning_level=3', 'cpp_std=c++20'],
)

libjamfactory_proj = subproject('libjamfactory')
libjamfactory_dep = libjamfactory_proj.get_variable('libjamfactory_dep')

sfml_dep = dependency('sfml-all')
spdlog_dep = dependency('spdlog')

dependencies = [libjamfactory_dep, sfml_dep, spdlog_dep]

executable(
  'jamfactory-client',
  'client/src/main.cpp',
  install: true,
  dependencies: dependencies,
)

executable(
  'jamfactory-server',
  'server/src/main.cpp',
  install: true,
  dependencies: dependencies,
)
