
if [[ ("$1" != "Server") && ("$1" != "Client")]]; then
  echo "Invalid argument!"
  echo "Usage: ./start.sh (Client | Server)"
else
  mkdir build
  cd build/ || exit

  if [[ "$1" == "Server" ]]; then
    app="Server"
  else
    app="graphify"
  fi

  qmake ../src/"$1"/"$app".pro
  make
  rm *.o

  echo "\n\n\n\n"
  echo "Build done!"
  echo "Starting application $1..."

  if [[ ("$1" == "Server")]]; then
    ./Server
  else
    ./***/**/*/graphify
  fi
fi