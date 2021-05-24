/* 
* Миллер Алиса Валентиновна
* Вариант 15
* Метод сортировки
* Сортировка прямым обменом (метод «пузырька»)
* Биллинговая база оператора связи
*    Система управления информацией о клиентах,
*    оказываемых им услугах и об оплате услуг.Поддерживаемые данные
*        ◦ Клиенты – физические лица и организации
*            ▪ Наименование или ФИО
*            ▪ Контакты : контактные лица, адрес(а), телефон(ы), e - mail(ы)
*            ▪ История услуг : услуги, в какое время оказывались 
*        ◦ Услуги
*            ▪ Наименование
*            ▪ Характеристики : номер, группа номеров, Интернет, SMS, спец.предложения
*            ▪ Тарифный план(какая часть услуги в какое время сколько будет стоить)
*        ◦ Счета клиентов
*            ▪ Баланс
*            ▪ Поступления на счет
*            ▪ Списания за оказание услуг связи
*            ▪ Ограничения : размер максимального кредита и сроки его погашения Поддерживаемые операции
*        ◦ Получение списка клиентов, в т.ч.по оказываемым услугам в заданном интервале времени, по характеристикам их счетов
*        ◦ Добавление и удаление данных о клиенте, чтение и редактирование данных о нем
*        ◦ Добавление и удаление услуги, чтение и редактирование данных о ней 
*/

#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void stamp()
{
  char name[] = "Student: Miller Alisa";
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  printf("\n%s\n", name);
  printf("%s", asctime(tm));
}

typedef struct listBills
{
  char fio[100];
  char minutes[10];
  int mins;
  char traffic[10];
  int mbytes;
  int rowsCount;
  struct listBills *next;
} listBills;
int COUNT = 0;
listBills *First = NULL;

int intRandom(int N)
{
  srand(time(NULL));
  return (rand() % N) + 1;
}
// Функция сортировки прямым обменом (метод "пузырька")
void swapArrayElements(listBills *array, int j)
{
  listBills temp = array[j - 1];
  array[j - 1] = array[j];
  array[j] = temp;
}
void bubbleSort(listBills *array, int size, int field)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = size - 1; j > i; j--)
    {
      switch (field)
      {
      case 1:
        if (array[j - 1].mins > array[j].mins)
          swapArrayElements(array, j);
        break;
      case 2:
        if (array[j - 1].mins < array[j].mins)
          swapArrayElements(array, j);
        break;
      case 3:
        if (array[j - 1].mbytes > array[j].mbytes)
          swapArrayElements(array, j);
        break;
      case 4:
        if (array[j - 1].mbytes < array[j].mbytes)
          swapArrayElements(array, j);
        break;
      default:
        printf("Не указано поле сортировки.\n");
        break;
      }
    }
  }
}

/*
 * *******************************************
 * Начало
 * Функции для создания односвязного списка
 * 
 * *******************************************
*/
/* Функция AddFirst добавляет новый элемент типа listBills в начало списка  */
void AddFirst(listBills **head, listBills *NewNode)
{
  //1. Выделяем память для нового структурного объекта
  listBills *newBill = (listBills *)malloc(sizeof(struct listBills));
  //2. Записываем данные в соответствующие поля
  strcpy(newBill->fio, NewNode->fio);
  strcpy(newBill->minutes, NewNode->minutes);
  newBill->mins = NewNode->mins;
  strcpy(newBill->traffic, NewNode->traffic);
  newBill->mbytes = NewNode->mbytes;
  //3. Делаем следующий элемент головой списка
  newBill->next = (*head);
  //4. голова указывает на новый элемент
  (*head) = newBill;
}

/* Функция AddLast добавляет новый элемент типа listBills в конец списка  */
void AddLast(listBills **head, listBills *NewNode)
{
  listBills *last = *head;
  //1. Выделяем память для нового структурного объекта
  listBills *newBill = (listBills *)malloc(sizeof(struct listBills));
  //2. Записываем данные в соответствующие поля
  strcpy(newBill->fio, NewNode->fio);
  strcpy(newBill->minutes, NewNode->minutes);
  newBill->mins = NewNode->mins;
  strcpy(newBill->traffic, NewNode->traffic);
  newBill->mbytes = NewNode->mbytes;
  //3. Новый элемент будет последним, обнуляем его.
  newBill->next = NULL;
  //4. Если список пуст, то добавляем новый элемент в качестве головы
  if (*head == NULL)
  {
    *head = newBill;
    return;
  }
  // 5. Иначе, переходим по ссылкам до последнего элемента
  while (last->next != NULL)
    last = last->next;
  // 6. Меняем указатель next последнего элемента
  last->next = newBill;
  return;
}

void insertNode(listBills *prev, listBills *NewNode)
{
  // 1. Проверяем первый аргумент на равество нулю.
  if (prev == NULL)
  {
    printf("the given previous node cannot be NULL");
    return;
  }
  // 2.
  listBills *newBill = (listBills *)malloc(sizeof(struct listBills));
  // 3.
  strcpy(newBill->fio, NewNode->fio);
  strcpy(newBill->minutes, NewNode->minutes);
  newBill->mins = NewNode->mins;
  strcpy(newBill->traffic, NewNode->traffic);
  newBill->mbytes = NewNode->mbytes;
  // 4. Меняем указатель next of нового узла на next предыдущего узла prev
  newBill->next = prev->next;
  // 5. Записываем в next предыдущего узла prev новый элемент
  prev->next = newBill;
}

/* Добавляем элемент в односвязный список*/
void AddNode(listBills **head, listBills *NewNode)
{
  listBills *prev, *p;
  p = NewNode;
  p->next = NULL;
  if (*head == NULL)
  { // особый случай, когда список пуст
    AddFirst(head, NewNode);
    return;
  }
  else
    AddLast(head, NewNode);
}

void PrintList(listBills *node)
{
  printf("|\tФИО\t\t|  Минуты  |  МБайт  |\n");
  printf("----------------------------------------------\n");
  while (node != NULL)
  {
    printf("%-28s \t|%7d   |%6d   |\n", node->fio, node->mins, node->mbytes);
    node = node->next;
  }
}
/*
 * *******************************************
 * 
 * Функции для создания односвязного списка
 * Конец
 * *******************************************
*/

/*
 * *******************************************
 * 
 * Функции для работы с базой данных
 * 
 * *******************************************
*/
static int callbackOrig(void *data, int argc, char **argv, char **azColName)
{
  int i;
  fprintf(stderr, "%s: \n", (const char *)data);
  for (i = 0; i < argc; i++)
  {
    printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void execChanges(char *sql, sqlite3 *db)
{
  int rc;
  char *zErrMsg = 0;
  const char *data = "Запись в БД";
  /* Execute SQL statement */

  rc = sqlite3_exec(db, sql, callbackOrig, (void *)data, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "Ошибка SQL: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    // fprintf(stdout, "Всё получилось!\n");
    // fprintf(stdout, "%s\n", sql);
  }
}

static int callbackNew(void *Table, int argc, char **argv, char **azColName)
{
  listBills *tmp = (listBills *)malloc(sizeof(struct listBills));
  tmp = (listBills *)Table;
  size_t i = 0;
  while (i < argc)
  {
    argv[i] ? strcpy(tmp->fio, argv[i]) : strcpy(tmp->fio, "NULL");
    i++;
    // argv[i] ? (tmp->mins = (int)(size_t)argv[i]) : (tmp->mins = 0);
    argv[i] ? strcpy(tmp->minutes, argv[i]) : strcpy(tmp->minutes, "NULL");
    argv[i] ? (tmp->mins = atoi(argv[i])) : (tmp->mins = 0);
    i++;
    argv[i] ? strcpy(tmp->traffic, argv[i]) : strcpy(tmp->traffic, "NULL");
    argv[i] ? (tmp->mbytes = atoi(argv[i])) : (tmp->mbytes = 0);
    i++;
    tmp->next = NULL;
    // i++;
  }
  printf("ФИО: %s Минуты: %s Трафик: %s\n", tmp->fio, tmp->minutes, tmp->traffic);
  COUNT++;
  AddNode(&First, tmp);
  // printf("head callback: %s data %s\n", Head->fio, Head->data);
  free(tmp);
  return 0;
}

void makeStruct(char *sql, sqlite3 *db)
{
  COUNT = 0;
  First = NULL;
  int rc;
  char *zErrMsg = 0;
  listBills *u = (listBills *)malloc(sizeof(listBills));

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, callbackNew, u, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "Ошибка SQL: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
}

/*
 * *******************************************
 * 
 * Создание и заполнение таблиц БД
 * 
 * *******************************************
*/

void createTable(sqlite3 *db)
{
  char *sql;
  /* Create SQL statement */
  sql = "CREATE TABLE Users("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL,"
        "Статус        CHAR(25)    NOT NULL,"
        "Компания      TEXT,"
        "ФИО           CHAR(75)    NOT NULL,"
        "Адрес         TEXT        NOT NULL,"
        "Телефон       CHAR(20)    NOT NULL,"
        "email         CHAR(25),"
        "Service_ID    INT         NOT NULL,"
        "Promo_ID      INT         NOT NULL,"
        "Баланс        REAL        NOT NULL);";
  execChanges(sql, db);
  sql = "CREATE TABLE Services("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL,"
        "Тариф         CHAR(100)  NOT NULL,"
        "Номер         CHAR(20)   NOT NULL,"
        "Время         INT        NOT NULL,"
        "Интернет      INT        NOT NULL,"
        "СМС           INT        NOT NULL);";
  execChanges(sql, db);

  sql = "CREATE TABLE Bills("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL,"
        "User_ID       INT        NOT NULL,"
        "Дата          DATETIME   NOT NULL,"
        "Минуты        INT        NOT NULL,"
        "Трафик        INT        NOT NULL,"
        "СМС           INT        NOT NULL);";
  execChanges(sql, db);
  sql = "CREATE TABLE Promotions("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT   NOT NULL,"
        "Акция         TEXT          NOT NULL);";
  execChanges(sql, db);
}
// Внесение демо-записей для тестирования
void dummyBills(sqlite3 *db)
{
  char sqll[1024];
  for (int i = 1; i < 25; i++)
  {
    snprintf(sqll, sizeof(sqll), "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) VALUES ( %d, datetime('now'), %d, %d, %d);", i % 6, intRandom(i * 8), intRandom(i * 12), intRandom(i * 7));
    execChanges(sqll, db);
  }
}

void dummyData(sqlite3 *db)
{
  char *sql, *date;
  /* Create SQL statement */
  sql = "INSERT INTO Users \
  (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) "
        "VALUES ('ФЛ', 'ФЛ', 'Евгений Вич Варкин','Москва, ул. Мясницкая', '+7(900)800-70-60', 'evgen@mobile.ru', 1, 1, 15000);"
        "INSERT INTO Users \
  (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) "
        "VALUES ('ФЛ', 'ФЛ', 'Чукигек Егоров','Москва, ул. Вавилова', '+7(900)888-77-66', 'gai@dar.ru', 3, 2, 25000);"
        "INSERT INTO Users \
  (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) "
        "VALUES ('ЮЛ', 'ЗАО ЙЕС', 'Анатолий Рыжиков','Москва, Сколково', '+7(900)100-10-10', 'chubice@sveta.net', 1, 3, 1500);"
        "INSERT INTO Users \
  (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) "
        "VALUES ('ЮЛ', 'ООО Вектор', 'Шнур Сергеев','Ленинград', '+7(999)111-12-34', 'leningrad@SPB.ru', 2, 4, 5000);"
        "INSERT INTO Users \
  (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) "
        "VALUES ('ФЛ', 'ФЛ', 'Швондер','Москва, ул. Пречистенка, 24', '+7(917)917-25-08', 'schwonder@dom.com', 2, 4, 15000);";
  execChanges(sql, db);

  sql = "INSERT INTO Services (Тариф, Номер, Время, Интернет, СМС) "
        "VALUES ('Бизнес', 'Золотой', 1000000, 1000000000, 1000); "
        "INSERT INTO Services (Тариф, Номер, Время, Интернет, СМС) "
        "VALUES ('Тарифчик', 'Серебрянный', 2000, 25000, 500); "
        "INSERT INTO Services (Тариф, Номер, Время, Интернет, СМС) "
        "VALUES ('Стандарт', 'Стандарт', 500, 10000, 200); ";
  execChanges(sql, db);

  dummyBills(db);

  // sql =
  //     "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) "
  //     "VALUES (1, datetime('now'), intRandom(50), intRandom(50), intRandom(50)); "
  //     "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) "
  //     "VALUES (2, datetime('now'), 112, 233, 22); "
  //     "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) "
  //     "VALUES (3, datetime('now'), 432, 2334, 32); "
  //     "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) "
  //     "VALUES (4, datetime('now'), 212, 544, 32); "
  //     "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) "
  //     "VALUES (5, datetime('now'), 123, 546, 253); ";

  // execChanges(sql, db);

  sql = "INSERT INTO Promotions (Акция) "
        "VALUES ('Без скидок'); "
        "INSERT INTO Promotions (Акция) "
        "VALUES ('Приведи друга и получи скидку 50%.'); "
        "INSERT INTO Promotions (Акция) "
        "VALUES ('Первые три месяца скидка 40%.'); "
        "INSERT INTO Promotions (Акция) "
        "VALUES ('3ГБ интернета в подарок!'); ";
  execChanges(sql, db);
}
/*
 * *******************************************
 * 
 * Основной функционал программы
 * 
 * *******************************************
*/
void insertUser(sqlite3 *db)
{
  char sql[1024], status[25], company[100], name[75], address[100], phone[20], email[25];
  int sID = 0, pID = 0;
  float balance;
  printf("Статус клиента (ФЛ, ЮЛ): ");
  fgets(status, 25, stdin);
  status[strcspn(status, "\r\n")] = 0;
  printf("Компания: ");
  fgets(company, 100, stdin);
  company[strcspn(company, "\r\n")] = 0;
  printf("ФИО клиента: ");
  fgets(name, 75, stdin);
  name[strcspn(name, "\r\n")] = 0;
  printf("Адрес клиента: ");
  fgets(address, 100, stdin);
  address[strcspn(address, "\r\n")] = 0;
  printf("Телефон клиента: ");
  fgets(phone, 20, stdin);
  phone[strcspn(phone, "\r\n")] = 0;
  printf("Email клиента: ");
  fgets(email, 25, stdin);
  email[strcspn(email, "\r\n")] = 0;
  printf("Тариф (1 - Бизнес, 2 - Стандарт, 3 - Эконом): ");
  scanf("%d", &sID);
  printf("Акция (число): ");
  scanf("%d", &pID);
  printf("Баланс клиента, руб: ");
  scanf("%f", &balance);

  /* Create SQL statement */
  snprintf(sql, sizeof(sql), "INSERT INTO Users (Статус, Компания, ФИО, Адрес, Телефон, email, Service_ID, Promo_ID, Баланс) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', %d, %d, %f );", status, company, name, address, phone, email, sID, pID, balance);
  // printf("%s\n", sql);
  execChanges(sql, db);
}

void insertService(sqlite3 *db)
{
  char sql[512], plan[100], phone[20];
  int time, inet, sms;

  printf("Название тарифа: ");
  fgets(plan, 100, stdin);
  plan[strcspn(plan, "\r\n")] = 0;
  printf("Статус номера (Золотой, Серебрянный, Стандарт): ");
  fgets(phone, 20, stdin);
  phone[strcspn(phone, "\r\n")] = 0;
  printf("Время разговора, минут: ");
  scanf("%d", &time);
  printf("Интеренет, МБайт/мес: ");
  scanf("%d", &inet);
  printf("СМС, штук/мес: ");
  scanf("%d", &sms);

  /* Create SQL statement */
  snprintf(sql, sizeof(sql), "INSERT INTO Services (Тариф, Номер, Время, Интернет, СМС) VALUES ('%s', '%s', %d, %d, %d);", plan, phone, time, inet, sms);
  execChanges(sql, db);
}

void insertBill(sqlite3 *db)
{
  char sql[512];
  int User_ID, date, time, inet, sms;
  printf("ID клиента: ");
  scanf("%d", &User_ID);
  printf("Время разговора, минут: ");
  scanf("%d", &time);
  printf("Интеренет трафик, МБайт: ");
  scanf("%d", &inet);
  printf("СМС, штук: ");
  scanf("%d", &sms);

  /* Create SQL statement */
  snprintf(sql, sizeof(sql), "INSERT INTO Bills (User_ID, Дата, Минуты, Трафик, СМС) VALUES ( %d, datetime('now'), %d, %d, %d);", User_ID, time, inet, sms);
  execChanges(sql, db);
}

void updateData(sqlite3 *db, char *table)
{
  int id;
  char sql[256], view[128], field[25], value[128];
  printf("Редактирование записи:\n");
  printf("Таблица %s. Найдите нужный ID.", table);
  snprintf(view, sizeof(view), "SELECT * from %s;", table);
  // view = "SELECT * from Users";
  execChanges(view, db);
  printf("Укажите ID для обновления: ");
  scanf("%d", &id);
  getchar();
  printf("Укажите поле для обновления: ");
  fgets(field, 25, stdin);
  field[strcspn(field, "\r\n")] = 0;
  // if (field == "Статус")
  printf("Введите новое значение: ");
  fgets(value, 128, stdin);
  value[strcspn(value, "\r\n")] = 0;

  snprintf(sql, sizeof(sql), "UPDATE %s set %s = '%s' where ID = %d;", table, field, value, id);
  printf("%s\n", sql);
  execChanges(sql, db);
}

void deleteData(sqlite3 *db, char *table)
{
  int id;
  char sql[128], view[128];
  printf("Удаление записи:\n");
  printf("Таблица %s. Найдите нужный ID.", table);
  snprintf(view, sizeof(view), "SELECT * from %s;", table);
  execChanges(view, db);
  printf("Укажите ID для удаления: ");
  scanf("%d", &id);
  snprintf(sql, sizeof(sql), "DELETE from %s where ID=%d;", table, id);
  execChanges(sql, db);
}

/*
 * *******************************************
 * 
 * Функции для создания отчётов
 * 
 * *******************************************
*/

void viewData(sqlite3 *db)
{
  int action;
  char *sql;
  do
  {
    printf("Просмотр таблиц БД:\n");
    printf("1.Клиенты; ");
    printf("2.Тарифы; ");
    printf("3.Счета; ");
    printf("4.Акции; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      sql = "SELECT * from Users";
      execChanges(sql, db);
      break;
    case 2:
      system("clear");
      sql = "SELECT * from Services";
      execChanges(sql, db);
      break;
    case 3:
      system("clear");
      sql = "SELECT * from Bills";
      execChanges(sql, db);
      break;
    case 4:
      system("clear");
      sql = "SELECT * from Promotions";
      execChanges(sql, db);
      break;
    case 5:
      break;
    default:
      system("clear");
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
}

void sortStruct(listBills *node, int field)
{
  listBills structArray[COUNT];
  int i = 0;

  while (node != NULL)
  {
    structArray[i] = *node;
    node = node->next;
    i++;
  }
  printf("|\tФИО\t\t|  Минуты  |  МБайт  |\n");
  printf("----------------------------------------------\n");
  for (int i = 0; i < COUNT; i++)
    printf("%-28s \t|%7d   |%6d   |\n", structArray[i].fio, structArray[i].mins, structArray[i].mbytes);
  bubbleSort(structArray, COUNT, field);
  printf("----------------------------------------------\n");
  for (int i = 0; i < COUNT; i++)
    printf("%-28s \t|%7d   |%6d   |\n", structArray[i].fio, structArray[i].mins, structArray[i].mbytes);
}

void sortedReport(char *sql, sqlite3 *db)
{
  int action;
  do
  {
    printf("\nСуммарный отчёт по клиентам с сортировкой:\n");
    printf("1.По времени разговора, по возрастанию; ");
    printf("2.По времени разговора, по убыванию; ");
    printf("3.По интернет траффику, по возрастанию; ");
    printf("4.По интернет траффику, по убыванию; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      printf("1. Сортировка по времени разговора, по возрастанию:\n\n");
      sortStruct(First, action);
      break;
    case 2:
      system("clear");
      printf("2.Сортировка по времени разговора, по убыванию:\n\n");
      sortStruct(First, action);
      break;
    case 3:
      system("clear");
      printf("3.Сортировка по интернет траффику, по возрастанию:\n\n");
      sortStruct(First, action);
      break;
    case 4:
      system("clear");
      printf("4.Сортировка по интернет траффику, по убыванию:\n\n");
      sortStruct(First, action);
      break;
    case 5:
      break;
    default:
      system("clear");
      printf("Отчёт без сортировки:\n");
      PrintList(First);
      break;
    }
  } while (action != 5);
  //
}

void reportsData(sqlite3 *db, char *table)
{
  int action;
  char *sql;
  do
  {
    printf("Отчёты по клиентам:\n");
    printf("1.По услугам общий; ");
    printf("2.По дате услуги; ");
    printf("3.По услугам детальный; ");
    printf("4.По услугам суммарный; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      printf("1. Отчёт по услугам общий:\n");
      sql = "SELECT Users.ФИО, SUM(Bills.Минуты) AS Минуты, SUM(Bills.Трафик) AS МБайт, SUM(Bills.СМС) AS СМС, Services.Тариф, Promotions.Акция from Bills JOIN Users ON Users.ID = Bills.User_ID  JOIN Services ON Users.Service_ID = Services.ID JOIN Promotions ON Users.Promo_ID = Promotions.ID GROUP BY User_ID ORDER BY User_ID ASC";
      execChanges(sql, db);
      break;
    case 2:
      system("clear");
      printf("2. Отчёт по дате услуги:\n");
      sql = "SELECT Users.ФИО, Bills.Дата, Bills.Минуты, Bills.Трафик from Bills JOIN Users ON (Users.ID = Bills.User_ID) ORDER BY User_ID ASC";
      execChanges(sql, db);
      break;
    case 3:
      system("clear");
      printf("3. Отчёт по услугам детальный:\n");
      sql = "SELECT Users.ФИО, Bills.Минуты, Bills.Трафик from Bills JOIN Users ON (Users.ID = Bills.User_ID) ORDER BY User_ID ASC";
      execChanges(sql, db);
      makeStruct(sql, db);
      sortedReport(sql, db);
      break;
    case 4:
      system("clear");
      printf("4. Отчёт по услугам суммарный с сортировкой:\n");
      sql = "SELECT Users.ФИО, SUM(Bills.Минуты) AS Минуты, SUM(Bills.Трафик) AS МБайт from Bills JOIN Users ON (Users.ID = Bills.User_ID) GROUP BY User_ID ORDER BY User_ID ASC";
      execChanges(sql, db);
      makeStruct(sql, db);
      sortedReport(sql, db);
      break;
    case 5:
      break;
    case 6:
      system("clear");
      printf("6. Отчёт до сортировки:\n");
      PrintList(First);
      sortedReport(sql, db);

      break;
    default:
      system("clear");
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
}

/*
 * *******************************************
 * 
 * Вызов основных функций из меню
 * 
 * *******************************************
*/

void usersData(sqlite3 *db)
{
  char *table = "Users";
  int action;
  do
  {
    printf("Клиенты:\n");
    printf("1.Новый; ");
    printf("2.Обновить; ");
    printf("3.Удалить; ");
    printf("4.Отчёты; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      insertUser(db);
      break;
    case 2:
      system("clear");
      updateData(db, table);
      break;
    case 3:
      system("clear");
      deleteData(db, table);
      break;
    case 4:
      system("clear");
      reportsData(db, table);
      break;
    case 5:
      break;
    default:
      system("clear");
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
}

void servicesData(sqlite3 *db)
{
  char *table = "Services";
  int action;
  do
  {
    printf("Услуги:\n");
    printf("1.Новая услуга; ");
    printf("2.Обновить; ");
    printf("3.Удалить; ");
    printf("4.Отчёты; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      insertService(db);
      break;
    case 2:
      system("clear");
      updateData(db, table);
      break;
    case 3:
      system("clear");
      deleteData(db, table);
      break;
    case 4:
      system("clear");
      reportsData(db, table);
      break;
    case 5:
      break;
    default:
      system("clear");
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
}

void billsData(sqlite3 *db)
{
  char *table = "Bills";
  int action;
  do
  {
    printf("Счета:\n");
    printf("1.Новая запись; ");
    printf("2.Обновить; ");
    printf("3.Удалить; ");
    printf("4.Отчёты; ");
    printf("5.Назад\n\n");
    printf("Введите номер команды: ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      system("clear");
      insertBill(db);
      break;
    case 2:
      system("clear");
      updateData(db, table);
      break;
    case 3:
      system("clear");
      deleteData(db, table);
      break;
    case 4:
      system("clear");
      reportsData(db, table);
      break;
    case 5:
      break;
    case 6:
      printf("Добавим героям расходов. В научных целях.\n");
      dummyBills(db);
      break;
    default:
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
}

int main(int argc, char *argv[])
{
  sqlite3 *db;
  int rc;
  // Открываем БД
  rc = sqlite3_open("./pz2/test.db", &db);
  if (rc)
  {
    fprintf(stderr, "Ошибка открытия БД: %s\n", sqlite3_errmsg(db));
    createTable(db);
    exit(404);
  }
  else
  {
    fprintf(stderr, "БД найдена и готова к работе.\n");
  }

  int action;
  do
  {
    printf("Главное меню\n");
    printf("1.Пользователи; ");
    printf("2.Услуги; ");
    printf("3.Счета; ");
    printf("4.Просмотр данных; ");
    printf("5.Выход\n\n");
    printf("Введите номер команды : ");
    scanf("%d", &action);
    getchar();
    switch (action)
    {
    case 1:
      usersData(db);
      break;
    case 2:
      servicesData(db);
      break;
    case 3:
      billsData(db);
      break;
    case 4:
      viewData(db);
      break;
    case 5:
      sqlite3_close(db);
      break;
    case 6:
      printf("Скрытая функция инициализации БД.\n");
      createTable(db);
      dummyData(db);
      break;
    default:
      printf("Ошибка ввода. Не ломай программу!\n");
      break;
    }
  } while (action != 5);
  stamp();
  return 0;
}
