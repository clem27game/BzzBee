
{ pkgs }: {
  deps = [
    pkgs.clang
    pkgs.ccls
    pkgs.gdb
    pkgs.gnumake
    pkgs.nodejs_18
    pkgs.python3
    pkgs.ruby
    pkgs.julia-bin
    pkgs.gcc
  ];
}
