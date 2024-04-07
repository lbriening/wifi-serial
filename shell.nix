with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "Arduino Environment";
  nativeBuildInputs = with pkgs; [
    platformio
    minicom
  ];
  buildInputs = [];
}
