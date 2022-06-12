{ stdenv, lib, fetchgit, cmake, boost, openssl, zlib, curl }:

stdenv.mkDerivation {
  name = "tgbot_cpp";

  src = fetchgit {
    url = "https://github.com/dan4ik605743/tgbot_cpp";
    sha256 = "sha256-PK+soGsXpNKVCdU/QJQ8MmoZAczBba5KvQOOk2kxglA=";
    deepClone = true;
  };

  nativeBuildInputs = [ 
    cmake 
  ];
  
  buildInputs = [ 
    boost 
    openssl 
    zlib 
    curl 
  ];

  meta = with lib; {
    description = "Telegram bot showing weather and exchange rates written in C++";
    homepage = "https://github.com/dan4ik605743/tgbot_cpp";
    license = licenses.mit;
    maintainers = with maintainers; [ dan4ik605743 ];
    platforms = platforms.linux;
  };
}
