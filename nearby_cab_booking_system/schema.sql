-- DBMS layer for "Finding Nearby Cabs"
CREATE TABLE users (
  id           INT PRIMARY KEY AUTO_INCREMENT,
  name         VARCHAR(80)  NOT NULL,
  phone        VARCHAR(20)  UNIQUE NOT NULL,
  last_lat     DECIMAL(9,6),
  last_lon     DECIMAL(9,6),
  updated_at   TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE cabs (
  id           INT PRIMARY KEY AUTO_INCREMENT,
  driver       VARCHAR(80) NOT NULL,
  plate        VARCHAR(20) UNIQUE NOT NULL,
  type         ENUM('Mini','Sedan','SUV','EV') NOT NULL,
  lat          DECIMAL(9,6) NOT NULL,   -- updated by the GPS tracker
  lon          DECIMAL(9,6) NOT NULL,
  available    BOOLEAN DEFAULT TRUE,
  rating       DECIMAL(2,1) DEFAULT 5.0,
  fare_per_km  DECIMAL(6,2) NOT NULL
);

CREATE TABLE rides (
  id           INT PRIMARY KEY AUTO_INCREMENT,
  user_id      INT NOT NULL REFERENCES users(id),
  cab_id       INT NOT NULL REFERENCES cabs(id),
  pickup_lat   DECIMAL(9,6) NOT NULL,
  pickup_lon   DECIMAL(9,6) NOT NULL,
  drop_lat     DECIMAL(9,6),
  drop_lon     DECIMAL(9,6),
  distance_km  DECIMAL(7,3),
  fare         DECIMAL(8,2),
  status       ENUM('requested','ongoing','completed','cancelled') DEFAULT 'requested',
  created_at   TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE payments (
  id            INT PRIMARY KEY AUTO_INCREMENT,
  ride_id       INT NOT NULL REFERENCES rides(id),
  gateway       VARCHAR(30) NOT NULL,      -- Razorpay / Stripe / UPI
  gateway_txn   VARCHAR(64) UNIQUE,
  amount        DECIMAL(8,2) NOT NULL,
  status        ENUM('pending','paid','failed','refunded') DEFAULT 'pending',
  paid_at       TIMESTAMP NULL
);

-- Bounding-box pre-filter so the C++ engine only computes the
-- great-circle distance for cabs that are plausibly close.
-- :lat, :lon = user location, :d = search radius in km
SELECT * FROM cabs
WHERE available = TRUE
  AND lat BETWEEN :lat - (:d / 111.0) AND :lat + (:d / 111.0)
  AND lon BETWEEN :lon - (:d / (111.0 * COS(RADIANS(:lat))))
              AND :lon + (:d / (111.0 * COS(RADIANS(:lat))));
