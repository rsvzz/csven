inc_src = include_directories('../../src', '../../include')
src_files = files([
    'comperetoindex.c',
    'createtobutton.c',
    'gridtobutton.c',
    'createtobtnforgrid.c',
    'createtoverb.c',
    'maptogridwithname.c',
    'optionverb.c',
    'app.c',
    'mapcss.c',
    'nav.c',
    'wordpg.c',
    'verbpg.c'
])

gtk_dep = dependency('gtk4')
questk_dep = declare_dependency(
  #include_directories: ['/usr/local/include'],
  link_args: ['-L/usr/local/lib', '-lquestk']
  )

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep, questk_dep]
)