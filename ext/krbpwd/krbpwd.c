#include <stdio.h>
#include <strings.h>
#include <kerberosv5/krb5.h>
#include <ruby.h>

//#define DEBUG

#define KADM5_CHANGEPW_SERVICE "kadmin/changepw"

VALUE cKrbPwd = Qnil;

VALUE change_passwd(VALUE self, VALUE v_user, VALUE v_old_pwd, VALUE v_new_pwd)
{
  Check_Type(v_user, T_STRING);
  Check_Type(v_old_pwd, T_STRING);
  Check_Type(v_new_pwd, T_STRING);
  char* user = StringValuePtr(v_user);
  char* old_pwd = StringValuePtr(v_old_pwd);
  char* new_pwd = StringValuePtr(v_new_pwd);
  int iRubyRetCode=-1;
  krb5_error_code             krbret;
  krb5_context                ctx;
  krb5_creds                  creds;
  krb5_principal              princ;
  int pw_result;
  krb5_data       pw_res_string, res_string;

  memset(&princ, 0, sizeof(princ));
  memset(&creds, 0, sizeof(creds));

#ifdef DEBUG
  printf("Old=%s\n", old_pwd);
  printf("New=%s\n", new_pwd);
#endif

  if ((krbret = krb5_init_context(&ctx))) {
#ifdef DEBUG
    printf("Error to init.\n");
#endif
    iRubyRetCode=1;
    return INT2NUM(iRubyRetCode);
  }

  if ((krbret = krb5_parse_name(ctx, user, &princ))) {
    krb5_free_context(ctx);
#ifdef DEBUG
    printf("Error to parse name.\n");
#endif
    iRubyRetCode=2;
    return INT2NUM(iRubyRetCode);
  }

  if ((krbret = krb5_get_init_creds_password( ctx, &creds, princ, old_pwd, NULL, NULL, 0, KADM5_CHANGEPW_SERVICE, NULL))) {
#ifdef DEBUG
    printf("Error to init cred %d %s.\n", krbret, error_message(krbret));
#endif
    krb5_free_principal(ctx, princ);
    krb5_free_context(ctx);
    iRubyRetCode=3;
    return INT2NUM(iRubyRetCode);
  }

  if ((krbret = krb5_change_password(ctx, &creds, new_pwd, &pw_result, &pw_res_string, &res_string ))) {
    iRubyRetCode=4;
    pw_result=0;
#ifdef DEBUG
    printf("Error set password.\n");
#endif
  }

  if (pw_result!=0) {
    iRubyRetCode=5;
#ifdef DEBUG
    printf("DEBUG: Fehler to change pwd.\n");
#endif
  }
  else {
    iRubyRetCode=0;
#ifdef DEBUG
    printf("DEBUG: Pwd changed.\n");
#endif
  }

  krb5_free_cred_contents(ctx, &creds);
  krb5_free_principal(ctx, princ);
  krb5_free_context(ctx);

  return INT2NUM(iRubyRetCode);
}


void Init_krbpwd()
{
  cKrbPwd     = rb_define_class("KrbPwd", rb_cObject);
  rb_define_method(cKrbPwd, "change_passwd", change_passwd, 3);

}
