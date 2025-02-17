
inc_src = '../../include'
src_files = files([
    'comperetoindex.c',
    'createtobutton.c',
    'gridtobutton.c',
    'createtobtnforgrid.c',
    'maptogridwithname.c'
])

gtk_dep = dependency('gtk4')
questk_dep = declare_dependency(
  #include_directories: ['/usr/local/include'],
  link_args: ['-L/usr/local/lib', '-lquestk']
  )

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    dependencies: [gtk_dep, questk_dep]
)