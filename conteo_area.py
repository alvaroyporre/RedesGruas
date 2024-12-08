import cv2
from ultralytics import YOLO
import urllib.request
import numpy as np
import time

# URL de ESP32-CAM
url = 'http://192.168.18.56/cam-hi.jpg'

# Cargar modelo YOLO
model = YOLO("best.pt")

# Región de interés (ROI)
roi_points = np.array([(185, 17), (443, 20), (453, 576), (125, 569)], 
                     np.int32).reshape((-1, 1, 2))

# Contadores para las clases
counter = {
    "container_blue": 0,
    "container_red": 0
}

# Establecer un conjunto para realizar un seguimiento de los objetos ya contados
counted_objects = set()

def is_in_region(bbox, region):
    """
    Verifica si el bounding box (bbox) está dentro de la región de interés (region).
    """
    x1, y1, x2, y2 = map(int, bbox)
    points = [(x1, y1), (x2, y1), (x2, y2), (x1, y2)]
    return all(cv2.pointPolygonTest(region, point, False) >= 0 for point in points)

# Temporizador para realizar la detección cada 10 segundos
last_detection_time = time.time()

while True:
    try:
        # Obtener imagen desde la ESP32-CAM
        imgResponse = urllib.request.urlopen(url)
        imgNp = np.array(bytearray(imgResponse.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgNp, -1)

        if frame is None:
            print("Error: No se recibió imagen válida.")
            continue

        # Rotar la imagen si es necesario
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)

        # Dibujar la región de interés (ROI) en la imagen
        cv2.polylines(frame, [roi_points], True, (0, 255, 0), 2)

        # Verificar si han pasado 10 segundos desde la última detección
        current_time = time.time()
        if current_time - last_detection_time >= 10:
            # Realizar la detección con YOLO
            results = model(frame)

            # Procesar resultados de la detección
            for r in results:
                boxes = r.boxes
                for box in boxes:
                    xyxy = box.xyxy[0].cpu().numpy()
                    conf = float(box.conf[0])
                    cls = int(box.cls[0])
                    class_name = model.names[cls]

                    # Verificar si la detección está dentro de la región de interés y si la confianza es mayor a 0.5
                    if conf > 0.5 and is_in_region(xyxy, roi_points):
                        # Crear un identificador único para cada objeto basado en las coordenadas de su bbox
                        object_id = (class_name, tuple(xyxy[:2]))  # Usamos la clase y la posición como id

                        # Si el objeto no ha sido contado, incrementamos el contador y lo agregamos al conjunto de objetos contados
                        if object_id not in counted_objects:
                            counter[class_name] += 1
                            counted_objects.add(object_id)

                        # Definir color para el bounding box según la clase
                        color = (0, 255, 0) if class_name == "container_blue" else (0, 0, 255)

                        # Dibujar el bounding box y la etiqueta en la imagen
                        cv2.rectangle(frame, 
                                      (int(xyxy[0]), int(xyxy[1])), 
                                      (int(xyxy[2]), int(xyxy[3])), 
                                      color, 2)
                        cv2.putText(frame, 
                                    f'{class_name} {conf:.2f}', 
                                    (int(xyxy[0]), int(xyxy[1]) - 10), 
                                    cv2.FONT_HERSHEY_SIMPLEX, 
                                    0.5, color, 2)

            # Actualizar el tiempo de la última detección
            last_detection_time = current_time

        # Mostrar contadores en la parte superior de la imagen
        cv2.putText(frame, 
                    f'Blue: {counter["container_blue"]} Red: {counter["container_red"]}', 
                    (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 
                    1, (255, 255, 255), 2)

        # Mostrar el frame en una ventana
        cv2.imshow("Container Detection ESP32-CAM", frame)

        # Salir al presionar 'ESC'
        if cv2.waitKey(1) & 0xFF == 27:
            break

    except Exception as e:
        print(f"Error: {e}")
        continue

# Cerrar ventanas y limpiar
cv2.destroyAllWindows()
