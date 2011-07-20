#

require 'mkmf'

extension_name = 'krbpwd'

dir_config(extension_name, '/usr/local')

have_header('krb5.h')
have_library('krb5')

create_makefile(extension_name)

