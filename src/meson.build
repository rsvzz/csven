inc_src = include_directories('../src', '../include')
#subdir('model')
subdir('model_gtk')
subdir('win')

#dont use more
#questk_dep = dependency('questk', required: true)
#questk_dep = declare_dependency(
#  link_args: ['-L/usr/local/lib', '-lquestk']
#)

#install style prefix
install_data('../style/io.github.rsvzz.csven.css', install_dir: get_option('prefix') / 'share/csven/style')
syslocal = host_machine.system()

# Instala el archivo solo en Linux
if syslocal == 'linux'
   install_data('../data/io.github.rsvzz.csven.svg', install_dir: get_option('prefix') / 'share/icons/hicolor/scalable/apps')
   install_data('../data/io.github.rsvzz.csven.metainfo.xml', install_dir: get_option('prefix') / 'share/metainfo')

   install_data(
    '../data/io.github.rsvzz.csven.desktop',
    install_dir: join_paths(get_option('prefix'), 'share/applications')
)
endif

gtk_dep = dependency('gtk4')

executable('csven',
  sources: 'main.c',
  include_directories: [inc_src],
  dependencies: [gtk_dep],
   link_with: [
      mgtk_dep, wingtk_dep
   ],
   install: true
  #link_args: ['/SUBSYSTEM:WINDOWS'] #windows,,
)