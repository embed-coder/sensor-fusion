pipeline {
  agent {
    kubernetes {
      label 'jnlp-agent'
      defaultContainer 'jnlp'
    }
  }
  
  stages {
    stage('error') {
      steps {
        sh '''apt update
apt install -y gcc g++ git autogen autoconf \\
                    build-essential cmake graphviz \\
                    libgtest-dev libtool pkg-config \\
                    libserial-dev

./build.sh'''
      }
    }

  }
}