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

    stage('test') {
      steps {
        sh './run_test.sh'
      }
    }

  }
}