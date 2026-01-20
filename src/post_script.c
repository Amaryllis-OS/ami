#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "post_script.h"
#include "kutil.h"

// chroot環境でpost_installスクリプトを実行する
int execute_post_install(const char* sh_file, const char* prefix) {
    // prefixがNULLまたは空の場合はデフォルトで"/"を使用
    const char* target_prefix = (prefix && prefix[0] != '\0') ? prefix : "/";
    
    // prefixディレクトリの存在確認
    struct stat st;
    if (stat(target_prefix, &st) == -1) {
        perror("stat failed on prefix");
        return -1;
    }
    
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "%s is not a directory\n", target_prefix);
        return -1;
    }
    
    // post_installスクリプトの存在確認
    if (access(sh_file, X_OK) == -1) {
        perror("access failed on post_install script");
        return -1;
    }
    
    // 子プロセスでchroot環境を作成
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }
    
    if (pid == 0) {
        if (chroot(target_prefix) == -1) {
            perror("chroot failed");
            exit(1);
        }
        
        // カレントディレクトリを変更
        if (chdir("/") == -1) {
            perror("chdir failed");
            exit(1);
        }
        
        // post_installスクリプトを実行
        // chroot環境ではスクリプトパスは"/"から始まる相対パスになる
        // 例: /tmp/ami_dist/pkginstall/post_install.sh -> /post_install.sh
        char* script = format_string(". /post_install.sh; post_install");
        
        if (execl("/usr/bin/sh", "-c", script, (char*)NULL) == -1) {
            perror("Failed to execute post-install script");
            free(script);
            exit(1);
        }

        if (remove("/post_install.sh")) {
            perror("Failed to remove post-install script after execution");
            free(script);
            exit(1);
        }

        free(script);
        exit(0);
    } else {
        // 親プロセス
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code != 0) {
                fprintf(stderr, "Post-install script failed with exit code %d\n", exit_code);
                return -1;
            }
        } else {
            fprintf(stderr, "Post-install script terminated abnormally\n");
            return -1;
        }
    }
    
    return 0;
}
