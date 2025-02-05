inc_src = '../include'
#subdir('model')
subdir('model_gtk')
subdir('win')

#questk_dep = dependency('questk', required: true)
questk_dep = declare_dependency(
  link_args: ['-L/usr/local/lib/x86_64-linux-gnu', '-lquestk']
)

 #install_data('../style/style.css', install_dir: get_option('prefix') / '/app/share/appgame/style')
 install_data('../style/style.css', install_dir: get_option('prefix') / '/usr/share/appgame/style')
gtk_dep = dependency('gtk4')
glib_dep = dependency('glib-2.0')

executable('appgame',
  sources: 'main.c',
  include_directories: [inc_src],
  dependencies: [gtk_dep, questk_dep, glib_dep],
   link_with: [
      mgtk_dep, wingtk_dep
   ],
   install: true
  #link_args: ['/SUBSYSTEM:WINDOWS'] #windows,,
)