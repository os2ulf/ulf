core = 7.x
api = 2

; Core
; As d.o is having issues with the update XML file, we are using this form for downloading core.
; See this: https://drupal.org/node/2126123
projects[drupal][type] = core
projects[drupal][version] = 7.23
projects[drupal][download][type] = get
projects[drupal][download][url] = http://ftp.drupal.org/files/projects/drupal-7.23.tar.gz
projects[drupal][patch][] = http://drupal.org/files/menu-get-item-rebuild-1232346-22_0.patch
projects[drupal][patch][] = http://drupal.org/files/ssl-socket-transports-1879970-13.patch
projects[drupal][patch][] = http://drupal.org/files/issues/autocomplete-1232416-17-7x.patch

; Get the profile, which will contain the next makefile.
projects[ulf][type] = "profile"
projects[ulf][download][type] = "git"
projects[ulf][download][url] = "git@github.com:uddannelse-laering-forloeb/ulf.git"
projects[ulf][download][branch] = "master"
