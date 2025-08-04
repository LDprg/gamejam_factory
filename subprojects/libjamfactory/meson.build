project('libjamfactory', 'cpp')

inc = include_directories('include')
libjamfactory = shared_library('jamfactory', include_directories: inc, install: true)

libjamfactory_dep = declare_dependency(include_directories: inc, link_with: libjamfactory)
