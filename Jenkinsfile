pipeline {
  agent any
  stages {
    stage('') {
      steps {
        sh '''sudo apt update
sudo apt install -y gcc g++ git autogen autoconf \\
                    build-essential cmake graphviz \\
                    libgtest-dev libtool pkg-config \\
                    libserial-dev

./build.sh'''
      }
    }

  }
}