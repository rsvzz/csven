inc_src = include_directories('../../src', '../../include')
src_files = files('cverbwin.c')

gtk_dep = dependency('libadwaita-1')
glib_dep = dependency('glib-2.0')
gobj_dep = dependency('gobject-2.0')

#questk_dep = declare_dependency(
#    #include_directories: ['/usr/local/include'],
#    link_args: ['-L/usr/local/lib', '-lquestk'],
#)

wingtk_dep = static_library(
    'm_win',
    sources: src_files,
    include_directories: [inc_src],
    dependencies: [gtk_dep, glib_dep, gobj_dep],
)