[![csven](https://snapcraft.io/csven/badge.svg)](https://snapcraft.io/csven)
# csven
CSVEN allows you to add an English word to mess it up and put it back together to learn how to write it through a game

# Get it from Snap Store
[![Get it from the Snap Store](https://snapcraft.io/en/dark/install.svg)](https://snapcraft.io/csven)

# Get it from Flathub
[![Get it on Flathub](https://flathub.org/api/badge?svg&locale=en)](https://flathub.org/apps/io.github.rsvzz.csven)



# Requirements
    libgtk-4-1
    questk
    
# Install questk
    git clone https://github.com/rsvzz/libquestk.git
    meson build
    ninja -C build
    cd build
    sudo ninja install

# Install
    meson build
    meson compile -C build
    cd build
    sudo ninja install
    
# Uninstall
    sudo ninja uninstall
