inc_src = include_directories('../../src', '../../include')
src_files = files([
    'appmain.c',
    'mapcss.c',
    'nav.c',
    'wordpg.c',
    'verbpg.c',
    'wordgame.c'
])

gtk_dep = dependency('libadwaita-1')
glib_dep = dependency('glib-2.0')
gobj_dep = dependency('gobject-2.0')

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep, glib_dep, gobj_dep]
)