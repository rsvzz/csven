inc_src = include_directories('../src', '../include')
#subdir('model')
subdir('model_gtk')
subdir('win')

#questk_dep = dependency('questk', required: true)
questk_dep = declare_dependency(
  link_args: ['-L/usr/local/lib', '-lquestk']
)

 #install_data('../style/style.css', install_dir: get_option('prefix') / '/app/share/csven/style')
 install_data('../style/io.github.rsvzz.csven.css', install_dir: get_option('prefix') / 'share/csven/style')
 # Verifica el sistema operativo
sistema_operativo = host_machine.system()

# Instala el archivo solo en Linux
if sistema_operativo == 'linux'

   #install_subdir('../fonts/monospace-font', install_dir: get_option('prefix') / 'share/fonts')
   install_data('../data/io.github.rsvzz.csven.desktop', install_dir: get_option('prefix') / 'share/applications')
   install_data('../data/io.github.rsvzz.csven.png', install_dir: get_option('prefix') / 'share/icons/hicolor/scalable/apps')
endif

 
gtk_dep = dependency('gtk4')
glib_dep = dependency('glib-2.0')

executable('csven',
  sources: 'main.c',
  include_directories: [inc_src],
  dependencies: [gtk_dep, questk_dep, glib_dep],
   link_with: [
      mgtk_dep, wingtk_dep
   ],
   install: true
  #link_args: ['/SUBSYSTEM:WINDOWS'] #windows,,
)