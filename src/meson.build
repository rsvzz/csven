inc_src = '../include'
subdir('model_gtk')

#questk_dep = dependency('questk', required: true)
questk_dep = declare_dependency(
  link_args: ['-L/usr/local/lib/x86_64-linux-gnu', '-lquestk']
)

 install_data('../style/style.css', install_dir: get_option('prefix') / '/usr/share/appgame/style')
gtk_dep = dependency('gtk4')

executable('appgame',
  sources: 'main.c',
  include_directories: [inc_src],
  dependencies: [gtk_dep, questk_dep],
   link_with: [
      mgtk_dep
   ],
   install: true
  #link_args: ['/SUBSYSTEM:WINDOWS'] #windows,,
)