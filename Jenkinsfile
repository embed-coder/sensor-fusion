pipeline {
  agent {
    kubernetes {
      inheritFrom 'jnlp-agent'
    }
  }
  
  stages {
    stage('build') {
      steps {
        sh './build.sh -a'
      }
    }

  }
}