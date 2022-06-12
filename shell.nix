{ pkgs ? import <nixpkgs> { } }: with pkgs;
mkShell {
  buildInputs = [
    cmake
    boost
    zlib
    openssl
    curl
  ];
}
