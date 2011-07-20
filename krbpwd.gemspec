require 'rubygems'

Gem::Specification.new do |spec|
  spec.name       = 'krbpwd'
  spec.version    = '0.2'
  spec.author     = 'Stephan Toggweiler'
  spec.license    = 'MIT'
  spec.email      = 'stephan@rheoli.net'
  spec.homepage   = 'http://www.rheoli.net'
  spec.platform   = Gem::Platform::RUBY
  spec.summary    = 'A Ruby interface for the the Kerberos library'
  spec.has_rdoc   = false
  #spec.test_files = Dir['test/test*']
  spec.extensions = ['ext/krbpwd/extconf.rb']
  spec.files      = Dir['**/*'].reject{ |f| f.include?('git') || f.include?('tmp') }
  
  #spec.rubyforge_project = 'krb5-auth'
  #spec.extra_rdoc_files  = ['README', 'CHANGES', 'MANIFEST'] + Dir['ext/krb5_auth/*.c']

  #spec.add_dependency('rake-compiler')
  
  #spec.add_development_dependency('test-unit', '>= 2.0.6')
  #spec.add_development_dependency('dbi-dbrc', '>= 1.1.6')
   
  spec.description = <<-EOF
    Interface to Kerberos for change password.
  EOF
end
