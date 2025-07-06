pipeline {
  agent {
    kubernetes {
      label 'jnlp-agent'
      defaultContainer 'jnlp'
      yaml """
apiVersion: v1
kind: Pod
spec:
  containers:
  - name: jnlp
    image: chuanna12/jenkins-inbound-agent:3309.v27b_9314fd1a_4-1
    args: ['\$(JENKINS_SECRET)', '\$(JENKINS_NAME)']
"""
    }
  }
  
  stages {
    stage('build') {
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