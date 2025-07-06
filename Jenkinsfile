pipeline {
  agent {
    kubernetes {
      label 'jnlp-agent'
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