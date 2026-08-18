pkgname=qalc
pkgver=0.1.0
pkgrel=1
pkgdesc="A simple desktop calculator developed in C++ using Qt"
arch=('x86_64')
url="https://github.com/Vitor-19/Qalc"
license=('MIT')
depends=('qt6-base')
makedepends=('cmake')

source=("$pkgname-$pkgver.tar.gz::https://github.com/Vitor-19/Qalc/archive/refs/tags/v$pkgver.tar.gz")
sha256sums=('30b3fe135bdd1e966499b0f5ef103f6d7b322ab8a231251f1ac0c349c713b950')

build() {
    cmake -B build -S "Qalc-$pkgver" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr

    cmake --build build
}

package() {
    DESTDIR="$pkgdir" cmake --install build
}
