//ESP32 Çift Çekirdek Kullanımı
TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pinleri
const int ledkirmizi = 2;
const int ledyesil = 4;

void setup() {
  Serial.begin(115200); 
  pinMode(ledkirmizi, OUTPUT);
  pinMode(ledyesil, OUTPUT);

  //Task1kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 0'da çalışacak şekilde ayarlıyoruz
  xTaskCreatePinnedToCore(
                    Task1kodu,   /* Görevin çalışacağı fonksiyon. */
                    "Task1",     /* Görevin adı. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /* ilave parametreler */
                    1,           /* Görevin önceliği */
                    &Task1,      /* Görevin işaretçisi */
                    0);          /* Görevi 0 numaralı çekirdeğe atayalım */                  
  delay(500); 

  //Task2kodu() fonksiyonunun çalışacağı görev bloğunu öncelik 1 olarak işlemci 1'de çalışacak şekilde ayarlıyoruz
  xTaskCreatePinnedToCore(
                    Task2kodu,   /* Görevin çalışacağı fonksiyon. */
                    "Task2",     /* Görevin adı. */
                    10000,       /* Görev stack boyutu */
                    NULL,        /* ilave parametreler */
                    1,           /* Görevin önceliği */
                    &Task2,      /* Görevin işaretçisi */
                    1);          /* Görevi 1 numaralı çekirdeğe atayalım */
    delay(500); 
}

//Task1kodu: Kırmızı ledi 2000 ms'de bir yakıp söndüreceğiz
void Task1kodu( void * pvParameters ){
  Serial.print("Task1'in Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID());

  for(;;){ //sonsuz döner
    digitalWrite(ledkirmizi, HIGH);
    delay(2000);
    digitalWrite(ledkirmizi, LOW);
    delay(500);
  } 
}

//Task2kodu: Yeşil ledi 300 ms'de bir yakıp söndüreceğiz
void Task2kodu( void * pvParameters ){
  Serial.print("Task2'nin Çalıştığı Çekirdek: ");
  Serial.println(xPortGetCoreID());

  for(;;){ //sonsuz döner
    digitalWrite(ledyesil, HIGH);
    delay(300);
    digitalWrite(ledyesil, LOW);
    delay(300);
  }
}

void loop() {
  
}
