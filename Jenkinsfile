pipeline {
  agent {
    kubernetes {
      inheritFrom 'jnlp-agent'
    }
  }

  triggers {
      githubPush()
  }
  
  stages {
    stage('build') {
      steps {
        sh './build.sh -a'
      }
    }

    stage('test') {
      steps {
        sh 'sudo ./run_test.sh'
      }
    }

  }
}