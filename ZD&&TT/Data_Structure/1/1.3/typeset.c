#include <stdio.h>
#include <string.h>

int main() {
    int colonPos;
    scanf("%d", &colonPos); // 读取冒号应该放置的位置

    FILE *fin = fopen("listin.txt", "r");
    FILE *fout = fopen("listout.txt", "w");
    char line[101]; // 假设每行最多100个字符

    while (fgets(line, sizeof(line), fin) != NULL) {
        char *colon = strchr(line, ':'); // 查找冒号
        if (colon != NULL) {
            // 处理左边的部分
            int leftLen = colon - line;
            char left[101] = {0};
            strncpy(left, line, leftLen);
            left[leftLen] = '\0'; // 确保字符串结束

            // 清理左边的空格
            char *token;
            char newLeft[101] = {0};
            token = strtok(left, " \t");
            while (token != NULL) {
                if (newLeft[0] != '\0') strcat(newLeft, " ");
                strcat(newLeft, token);
                token = strtok(NULL, " \t");
            }

            int spaceCount = colonPos - strlen(newLeft) - 2; // 计算需要填充的空格数量

            // 处理右边的部分
            char right[101] = {0};
            strcpy(right, colon + 1);
            
            // 清理右边的空格
            char newRight[101] = {0};
            token = strtok(right, " \t");
            while (token != NULL) {
                if (newRight[0] != '\0') strcat(newRight, " ");
                strcat(newRight, token);
                token = strtok(NULL, " \t");
            }

            // 写入文件
            fprintf(fout, "%s ", newLeft);
            for (int i = 0; i < spaceCount; i++) fputc(' ', fout);
            fprintf(fout, ": %s", newRight);
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
