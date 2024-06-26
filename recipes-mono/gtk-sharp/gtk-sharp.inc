SUMMARY = "GUI toolkit for Mono"
DESCRIPTION = "GTK+ bindings for Mono"
SECTION = "devel/mono"
BUGTRACKER = "http://bugzilla.xamarin.com"
LICENSE = "LGPL-2.1-only"
RDEPENDS:${PN}-dev += "perl"

inherit autotools
inherit mono

# For some reason the URL template changes from version to version,
# therefore use some variables for the directory and extension
SRC_URI = "http://download.mono-project.com/sources/gtk-sharp${SDIRVER}/gtk-sharp-${PV}.tar.${SEXT}"

SDIRVER = "${@gtk_sharp_download_version(d)}"
SEXT ??= "bz2"

def gtk_sharp_download_version(d):
    pvsplit = d.getVar('PV', True).split('.')
    return pvsplit[0] + '' + pvsplit[1]

FILESPATH =. "${FILE_DIRNAME}/gtk-sharp-${PV}:"

FILES:${PN} += "\
  ${libdir}/*.so \
"

FILES:${PN}-dev = "\
  ${libdir}/*.la \
  ${libdir}/pkgconfig/* \
  ${libdir}/${PN}*/* \
  ${datadir}/* \
"

do_install:append() {
  find ${D} -name *.dll -exec chown -h root:root {} \;
}
