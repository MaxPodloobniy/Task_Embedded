#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 512
#define MAX_ENTITY_SIZE 50
#define MAX_ENTITIES 10

// Функція для вставки нової сутності в відсортований масив сутностей.
void insertEntity(char entityList[MAX_ENTITIES][MAX_ENTITY_SIZE], int *entityCount, const char entity[MAX_ENTITY_SIZE]) {
    int i;

    // Починаємо з кінця масиву і рухаємось назад, доки не знайдемо відповідне місце для вставки.
    for (i = *entityCount - 1; i >= 0 && strcmp(entity, entityList[i]) < 0; i--) {
        // Зсуваємо сутності, які більші за нову сутність, вправо.
        strcpy(entityList[i + 1], entityList[i]);
    }
    // Вставляємо нову сутність на знайдене місце.
    strcpy(entityList[i + 1], entity);

    // Збільшуємо лічильник сутностей після вставки нової сутності.
    (*entityCount)++;
}


void extractAndSortEntities(const char inputString[MAX_STRING_SIZE]) {
    char entityList[MAX_ENTITIES][MAX_ENTITY_SIZE];
    int entityCount = 0;

    // Індекс для переходу по рядку
    int currentIndex = 0;

    // Пошук та обробка конструкцій перерахування
    while (inputString[currentIndex] != '\0') {
        char object[MAX_ENTITY_SIZE];
        int objectIndex = 0;

        // Пропуск пробілів та ком
        while (inputString[currentIndex] == ' ' || inputString[currentIndex] == ',') {
            currentIndex++;
        }

        // Знаходження об'єкту
        while (inputString[currentIndex] != ':' && inputString[currentIndex] != '\0') {
            object[objectIndex++] = inputString[currentIndex];
            currentIndex++;
        }
        object[objectIndex] = '\0';

        // Пропуск символу ':'
        currentIndex++;

        // Знаходження та сортування сутностей
        while (inputString[currentIndex] != ';' && inputString[currentIndex] != '\0') {
            char entity[MAX_ENTITY_SIZE];
            int entityIndex = 0;

            // Пропуск пробілів та ком
            while (inputString[currentIndex] == ' ' || inputString[currentIndex] == ',') {
                currentIndex++;
            }

            // Знаходження сутності
            while (inputString[currentIndex] != ',' && inputString[currentIndex] != ';' && inputString[currentIndex] != '\0') {
                entity[entityIndex++] = inputString[currentIndex];
                currentIndex++;
            }
            entity[entityIndex] = '\0';

            // Додавання сутності в список та сортування
            insertEntity(entityList, &entityCount, entity);
        }

        // Пропуск символу ';'
        currentIndex++;

        // Виведення результату, якщо є об'єкт і хоча б одна сутність
        if (strlen(object) > 0 && entityCount > 0) {
            printf("Об'єкт: %s \nСутності: ", object);
            // Виведення всіх сутностей з комами
            for (int i = 0; i < entityCount; i++) {
                printf("%s%s", i == 0 ? "" : ", ", entityList[i]);
            }
            printf("\n");
        }

        // Збільшення лічильника сутностей та очищення списку
        entityCount = 0;
        memset(entityList, 0, sizeof(entityList));
    }
}

int main() {
    char inputString[MAX_STRING_SIZE];

    // Введення рядка
    printf("Введіть речення: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Видалення символу нового рядка (\n), який залишається в кінці зчитаного рядка
    size_t len = strlen(inputString);
    if (len > 0 && inputString[len - 1] == '\n') {
        inputString[len - 1] = '\0';
    }

    // Виклик функції для обробки та виведення результату
    extractAndSortEntities(inputString);

    return 0;
}
