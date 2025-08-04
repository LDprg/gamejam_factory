project('libjamfactory', 'cpp')

spdlog_dep = dependency('spdlog')

inc = include_directories('include')

libjamfactory = library(
  'jamfactory',
  'src/logger.cpp',
  include_directories: inc,
  install: true,
  dependencies: [spdlog_dep],
)

libjamfactory_dep = declare_dependency(
  include_directories: inc,
  dependencies: [spdlog_dep],
  link_with: libjamfactory,
)
