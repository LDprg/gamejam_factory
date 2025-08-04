project(
  'gamejam_factory',
  'cpp',
  version: '0.1',
  meson_version: '>= 1.3.0',
  default_options: ['warning_level=3', 'cpp_std=c++20'],
)

sfml_dep = dependency('sfml-all')

dependencies = [sfml_dep]

executable(
  'gamejam_factory',
  'gamejam_factory.cpp',
  install: true,
  dependencies: dependencies,
)
