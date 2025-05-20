inc_src = include_directories('../../src', '../../include')
src_files = files('cverbwin.c', 'app.c')

adw_dep = dependency('libadwaita-1')
questk_dep = declare_dependency(
    #include_directories: ['/usr/local/include'],
    link_args: ['-L/usr/local/lib', '-lquestk'],
)

wingtk_dep = static_library(
    'm_adw',
    sources: src_files,
    include_directories: [inc_src],
    dependencies: [adw_dep, questk_dep],
)