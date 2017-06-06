-- MySQL dump 10.13  Distrib 5.7.17, for Linux (x86_64)
--
-- Host: localhost    Database: bme
-- ------------------------------------------------------
-- Server version	5.7.17-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `gameData`
--

DROP TABLE IF EXISTS `gameData`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gameData` (
  `timestamp` bigint(11) NOT NULL,
  `gameSessionId` int(11) NOT NULL,
  `handPalmX` float(7,4) DEFAULT NULL,
  `handPalmY` float(7,4) DEFAULT NULL,
  `handPalmZ` float(7,4) DEFAULT NULL,
  `palmNormalX` float(7,4) DEFAULT NULL,
  `palmNormalY` float(7,4) DEFAULT NULL,
  `palmNormalZ` float(7,4) DEFAULT NULL,
  `wristPositionX` float(7,4) DEFAULT NULL,
  `wristPositionY` float(7,4) DEFAULT NULL,
  `wristPositionZ` float(7,4) DEFAULT NULL,
  `thumbMetacarpalX` float(7,4) DEFAULT NULL,
  `thumbMetacarpalY` float(7,4) DEFAULT NULL,
  `thumbMetacarpalZ` float(7,4) DEFAULT NULL,
  `thumbProximalX` float(7,4) DEFAULT NULL,
  `thumbProximalY` float(7,4) DEFAULT NULL,
  `thumbProximalZ` float(7,4) DEFAULT NULL,
  `thumbIntermediateX` float(7,4) DEFAULT NULL,
  `thumbIntermediateY` float(7,4) DEFAULT NULL,
  `thumbIntermediateZ` float(7,4) DEFAULT NULL,
  `thumbDistalX` float(7,4) DEFAULT NULL,
  `thumbDistalY` float(7,4) DEFAULT NULL,
  `thumbDistalZ` float(7,4) DEFAULT NULL,
  `thumbTipX` float(7,4) DEFAULT NULL,
  `thumbTipY` float(7,4) DEFAULT NULL,
  `thumbTipZ` float(7,4) DEFAULT NULL,
  `indexMetacarpalX` float(7,4) DEFAULT NULL,
  `indexMetacarpalY` float(7,4) DEFAULT NULL,
  `indexMetacarpalZ` float(7,4) DEFAULT NULL,
  `indexProximalX` float(7,4) DEFAULT NULL,
  `indexProximalY` float(7,4) DEFAULT NULL,
  `indexProximalZ` float(7,4) DEFAULT NULL,
  `indexIntermediateX` float(7,4) DEFAULT NULL,
  `indexIntermediateY` float(7,4) DEFAULT NULL,
  `indexIntermediateZ` float(7,4) DEFAULT NULL,
  `indexDistalX` float(7,4) DEFAULT NULL,
  `indexDistalY` float(7,4) DEFAULT NULL,
  `indexDistalZ` float(7,4) DEFAULT NULL,
  `indexTipX` float(7,4) DEFAULT NULL,
  `indexTipY` float(7,4) DEFAULT NULL,
  `indexTipZ` float(7,4) DEFAULT NULL,
  `middleMetacarpalX` float(7,4) DEFAULT NULL,
  `middleMetacarpalY` float(7,4) DEFAULT NULL,
  `middleMetacarpalZ` float(7,4) DEFAULT NULL,
  `middleProximalX` float(7,4) DEFAULT NULL,
  `middleProximalY` float(7,4) DEFAULT NULL,
  `middleProximalZ` float(7,4) DEFAULT NULL,
  `middleIntermediateX` float(7,4) DEFAULT NULL,
  `middleIntermediateY` float(7,4) DEFAULT NULL,
  `middleIntermediateZ` float(7,4) DEFAULT NULL,
  `middleDistalX` float(7,4) DEFAULT NULL,
  `middleDistalY` float(7,4) DEFAULT NULL,
  `middleDistalZ` float(7,4) DEFAULT NULL,
  `middleTipX` float(7,4) DEFAULT NULL,
  `middleTipY` float(7,4) DEFAULT NULL,
  `middleTipZ` float(7,4) DEFAULT NULL,
  `ringMetacarpalX` float(7,4) DEFAULT NULL,
  `ringMetacarpalY` float(7,4) DEFAULT NULL,
  `ringMetacarpalZ` float(7,4) DEFAULT NULL,
  `ringProximalX` float(7,4) DEFAULT NULL,
  `ringProximalY` float(7,4) DEFAULT NULL,
  `ringProximalZ` float(7,4) DEFAULT NULL,
  `ringIntermediateX` float(7,4) DEFAULT NULL,
  `ringIntermediateY` float(7,4) DEFAULT NULL,
  `ringIntermediateZ` float(7,4) DEFAULT NULL,
  `ringDistalX` float(7,4) DEFAULT NULL,
  `ringDistalY` float(7,4) DEFAULT NULL,
  `ringDistalZ` float(7,4) DEFAULT NULL,
  `ringTipX` float(7,4) DEFAULT NULL,
  `ringTipY` float(7,4) DEFAULT NULL,
  `ringTipZ` float(7,4) DEFAULT NULL,
  `pinkyMetacarpalX` float(7,4) DEFAULT NULL,
  `pinkyMetacarpalY` float(7,4) DEFAULT NULL,
  `pinkyMetacarpalZ` float(7,4) DEFAULT NULL,
  `pinkyProximalX` float(7,4) DEFAULT NULL,
  `pinkyProximalY` float(7,4) DEFAULT NULL,
  `pinkyProximalZ` float(7,4) DEFAULT NULL,
  `pinkyIntermediateX` float(7,4) DEFAULT NULL,
  `pinkyIntermediateY` float(7,4) DEFAULT NULL,
  `pinkyIntermediateZ` float(7,4) DEFAULT NULL,
  `pinkyDistalX` float(7,4) DEFAULT NULL,
  `pinkyDistalY` float(7,4) DEFAULT NULL,
  `pinkyDistalZ` float(7,4) DEFAULT NULL,
  `pinkyTipX` float(7,4) DEFAULT NULL,
  `pinkyTipY` float(7,4) DEFAULT NULL,
  `pinkyTipZ` float(7,4) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`gameSessionId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gameData`
--

LOCK TABLES `gameData` WRITE;
/*!40000 ALTER TABLE `gameData` DISABLE KEYS */;
/*!40000 ALTER TABLE `gameData` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-03-07 19:55:52
