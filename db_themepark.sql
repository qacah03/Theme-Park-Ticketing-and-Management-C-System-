-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 16, 2024 at 03:21 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_themepark`
--

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `BOOKING_ID` int(11) NOT NULL,
  `BOOKING_DATE` date NOT NULL,
  `TOTAL_BOOKING` int(11) NOT NULL,
  `STAFF_ID` int(11) NOT NULL,
  `CUST_ID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`BOOKING_ID`, `BOOKING_DATE`, `TOTAL_BOOKING`, `STAFF_ID`, `CUST_ID`) VALUES
(1000, '2024-01-03', 1, 105, 202),
(1001, '2023-12-05', 1, 106, 205),
(1002, '2024-01-20', 5, 106, 202),
(1003, '2024-01-10', 6, 106, 201),
(1004, '2024-02-12', 9, 104, 205),
(1005, '2024-03-20', 2, 104, 206),
(1006, '2024-04-20', 7, 109, 207),
(1007, '2024-02-20', 5, 105, 202),
(1008, '2024-02-20', 4, 104, 204),
(1009, '2024-03-20', 3, 108, 202),
(1010, '2024-03-20', 4, 104, 202),
(1011, '2024-06-20', 6, 105, 223),
(1012, '2024-05-20', 15, 109, 224),
(1013, '2024-07-20', 9, 108, 220),
(1014, '2024-08-10', 6, 108, 207),
(1015, '2024-09-13', 8, 106, 221),
(1016, '2024-10-24', 19, 105, 203),
(1017, '2024-11-20', 4, 106, 202),
(1018, '2024-12-12', 8, 104, 204),
(1019, '2024-11-20', 3, 106, 204),
(1020, '2024-07-20', 4, 109, 223),
(1021, '2024-04-12', 5, 108, 224),
(1022, '2024-07-30', 5, 108, 202),
(1023, '2024-10-20', 7, 105, 202),
(1024, '2024-12-23', 6, 105, 203),
(1025, '2024-08-11', 4, 109, 221),
(1026, '2024-11-11', 4, 104, 225),
(1027, '2024-12-20', 4, 112, 202),
(1028, '2024-09-12', 4, 112, 202),
(1029, '2024-05-11', 4, 106, 225),
(1030, '2024-12-05', 2, 112, 225),
(1031, '2024-03-12', 4, 109, 225),
(1032, '2024-09-12', 4, 112, 225),
(1033, '2024-03-13', 5, 112, 224),
(1034, '2024-06-14', 3, 104, 224),
(1035, '2024-07-12', 3, 106, 221),
(1036, '2024-08-20', 5, 104, 220),
(1037, '2024-01-16', 5, 105, 221),
(1038, '2024-03-14', 5, 108, 221),
(1039, '2024-05-21', 21, 112, 221),
(1040, '2024-09-13', 5, 108, 221),
(1041, '2024-12-12', 5, 106, 221),
(1042, '2024-11-18', 5, 112, 221),
(1043, '2024-03-09', 5, 104, 221),
(1044, '2024-04-15', 5, 106, 221),
(1045, '2024-09-13', 5, 105, 221),
(1046, '2024-02-12', 5, 104, 203),
(1047, '2024-04-12', 5, 108, 203),
(1048, '2024-06-12', 5, 112, 202),
(1049, '2024-06-14', 5, 104, 207),
(1050, '2024-06-12', 5, 104, 204);

-- --------------------------------------------------------

--
-- Table structure for table `booking_category`
--

CREATE TABLE `booking_category` (
  `BOOKCAT_ID` int(11) NOT NULL,
  `BOOKING_ID` int(11) NOT NULL,
  `CATEGORY_ID` int(11) NOT NULL,
  `TOTAL` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `booking_category`
--

INSERT INTO `booking_category` (`BOOKCAT_ID`, `BOOKING_ID`, `CATEGORY_ID`, `TOTAL`) VALUES
(5000, 1000, 3003, 1),
(5001, 1001, 3002, 1),
(5002, 1002, 3002, 2),
(5003, 1002, 3003, 3),
(5004, 1003, 3002, 3),
(5005, 1003, 3003, 2),
(5006, 1003, 3004, 1),
(5007, 1004, 3001, 3),
(5008, 1004, 3002, 2),
(5009, 1004, 3003, 3),
(5010, 1004, 3004, 1),
(5011, 1005, 3003, 2),
(5012, 1006, 3002, 3),
(5013, 1006, 3003, 3),
(5014, 1006, 3004, 1),
(5015, 1007, 3003, 3),
(5016, 1007, 3004, 2),
(5017, 1008, 3002, 2),
(5018, 1008, 3003, 2),
(5019, 1010, 3002, 2),
(5020, 1010, 3003, 2),
(5021, 1011, 3001, 2),
(5022, 1011, 3002, 1),
(5023, 1011, 3003, 2),
(5024, 1011, 3004, 1),
(5025, 1012, 3001, 1),
(5026, 1012, 3002, 2),
(5027, 1012, 3003, 3),
(5028, 1012, 3004, 4),
(5029, 1012, 3005, 5),
(5030, 1013, 3002, 3),
(5031, 1013, 3003, 3),
(5032, 1013, 3004, 3),
(5033, 1014, 3002, 1),
(5034, 1014, 3003, 2),
(5035, 1014, 3004, 3),
(5036, 1015, 3002, 2),
(5037, 1015, 3003, 3),
(5038, 1015, 3004, 3),
(5039, 1016, 3001, 4),
(5040, 1016, 3002, 4),
(5041, 1016, 3003, 4),
(5042, 1016, 3004, 4),
(5043, 1016, 3005, 3),
(5044, 1017, 3002, 2),
(5045, 1017, 3003, 2),
(5046, 1018, 3001, 1),
(5047, 1018, 3002, 2),
(5048, 1018, 3003, 3),
(5049, 1018, 3004, 1),
(5050, 1018, 3005, 1),
(5051, 1019, 3002, 1),
(5052, 1019, 3003, 1),
(5053, 1019, 3004, 1),
(5054, 1020, 3001, 1),
(5055, 1020, 3002, 1),
(5056, 1020, 3003, 1),
(5057, 1020, 3004, 1),
(5058, 1021, 3002, 2),
(5059, 1021, 3003, 3),
(5060, 1022, 3002, 2),
(5061, 1022, 3003, 2),
(5062, 1022, 3004, 1),
(5063, 1023, 3002, 2),
(5064, 1023, 3003, 3),
(5065, 1023, 3004, 2),
(5066, 1024, 3002, 3),
(5067, 1024, 3003, 2),
(5068, 1024, 3004, 1),
(5069, 1025, 3002, 1),
(5070, 1025, 3003, 1),
(5071, 1025, 3004, 2),
(5072, 1026, 3003, 2),
(5073, 1026, 3004, 2),
(5074, 1027, 3001, 1),
(5075, 1027, 3002, 1),
(5076, 1027, 3003, 1),
(5077, 1027, 3004, 1),
(5078, 1028, 3002, 2),
(5079, 1028, 3003, 1),
(5080, 1028, 3004, 1),
(5081, 1029, 3001, 1),
(5082, 1029, 3002, 1),
(5083, 1029, 3003, 1),
(5084, 1029, 3004, 1),
(5085, 1030, 3003, 2),
(5086, 1031, 3001, 1),
(5087, 1031, 3002, 1),
(5088, 1031, 3003, 1),
(5089, 1031, 3004, 1),
(5090, 1032, 3001, 1),
(5091, 1032, 3002, 1),
(5092, 1032, 3004, 2),
(5093, 1033, 3001, 1),
(5094, 1033, 3002, 2),
(5095, 1033, 3003, 1),
(5096, 1033, 3004, 1),
(5097, 1034, 3003, 3),
(5098, 1035, 3002, 1),
(5099, 1035, 3003, 1),
(5100, 1035, 3004, 1),
(5101, 1036, 3001, 1),
(5102, 1036, 3002, 1),
(5103, 1036, 3003, 1),
(5104, 1036, 3004, 1),
(5105, 1036, 3005, 1),
(5106, 1037, 3001, 1),
(5107, 1037, 3002, 1),
(5108, 1037, 3003, 1),
(5109, 1037, 3004, 1),
(5110, 1037, 3005, 1),
(5111, 1038, 3001, 1),
(5112, 1038, 3002, 1),
(5113, 1038, 3003, 1),
(5114, 1038, 3004, 1),
(5115, 1038, 3005, 1),
(5116, 1039, 3001, 5),
(5117, 1039, 3002, 5),
(5118, 1039, 3003, 5),
(5119, 1039, 3004, 5),
(5120, 1039, 3005, 1),
(5121, 1040, 3001, 1),
(5122, 1040, 3002, 1),
(5123, 1040, 3003, 1),
(5124, 1040, 3004, 1),
(5125, 1040, 3005, 1),
(5126, 1041, 3001, 1),
(5127, 1041, 3002, 1),
(5128, 1041, 3003, 1),
(5129, 1041, 3004, 1),
(5130, 1041, 3005, 1),
(5131, 1042, 3001, 1),
(5132, 1042, 3002, 1),
(5133, 1042, 3003, 1),
(5134, 1042, 3004, 1),
(5135, 1042, 3005, 1),
(5136, 1043, 3001, 1),
(5137, 1043, 3002, 1),
(5138, 1043, 3003, 1),
(5139, 1043, 3004, 1),
(5140, 1043, 3005, 1),
(5141, 1044, 3001, 1),
(5142, 1044, 3002, 1),
(5143, 1044, 3003, 1),
(5144, 1044, 3004, 1),
(5145, 1044, 3005, 1),
(5146, 1045, 3001, 1),
(5147, 1045, 3002, 1),
(5148, 1045, 3003, 1),
(5149, 1045, 3004, 1),
(5150, 1045, 3005, 1),
(5151, 1046, 3001, 1),
(5152, 1046, 3002, 1),
(5153, 1046, 3003, 1),
(5154, 1046, 3004, 1),
(5155, 1046, 3005, 1),
(5156, 1047, 3001, 1),
(5157, 1047, 3002, 1),
(5158, 1047, 3003, 1),
(5159, 1047, 3004, 1),
(5160, 1047, 3005, 1),
(5161, 1048, 3001, 1),
(5162, 1048, 3002, 1),
(5163, 1048, 3003, 1),
(5164, 1048, 3004, 1),
(5165, 1048, 3005, 1),
(5166, 1049, 3001, 1),
(5167, 1049, 3002, 1),
(5168, 1049, 3003, 1),
(5169, 1049, 3004, 1),
(5170, 1049, 3005, 1),
(5171, 1050, 3001, 1),
(5172, 1050, 3002, 1),
(5173, 1050, 3003, 1),
(5174, 1050, 3004, 1),
(5175, 1050, 3005, 1);

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE `category` (
  `CATEGORY_ID` int(11) NOT NULL,
  `CATEGORY_NAME` varchar(100) NOT NULL,
  `CATEGORY_PRICE` double NOT NULL,
  `CATEGORY_AVAILABILITY` int(11) NOT NULL,
  `PROMOTIONS` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `category`
--

INSERT INTO `category` (`CATEGORY_ID`, `CATEGORY_NAME`, `CATEGORY_PRICE`, `CATEGORY_AVAILABILITY`, `PROMOTIONS`) VALUES
(3001, 'BABY', 0, 235, 1),
(3002, 'CHILD', 50, 180, 1),
(3003, 'ADULT', 80, 124, 0.9),
(3004, 'SENIOR', 40, 183, 0.95),
(3005, 'COMBO', 315, 244, 1);

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `CUST_ID` int(10) NOT NULL,
  `CUST_PHONE` char(12) NOT NULL,
  `CUST_NAME` varchar(100) NOT NULL,
  `CUST_USERNAME` varchar(50) NOT NULL,
  `CUST_PASSWORD` varchar(12) NOT NULL,
  `CUST_ADDRESS` varchar(100) NOT NULL,
  `CUST_EMAIL` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`CUST_ID`, `CUST_PHONE`, `CUST_NAME`, `CUST_USERNAME`, `CUST_PASSWORD`, `CUST_ADDRESS`, `CUST_EMAIL`) VALUES
(201, '019-4749115', 'MUHAMMAD HAZIQ', 'Muhammad_haziq', 'Haziq201_', 'NO 1, TAMAN CANTIK, 32130, TUMPAT, KELANTAN', 'Muhammadhaziq@gmail.com'),
(202, '011-6547878', 'NUR ANIS', 'Nur_anis', 'Anis202_', 'NO 11, TAMAN PAMERAN, 31230, KELBANG, PERAK', 'Nuranis@gmail.com\r\n'),
(203, '011-1231111', 'Mohd Najwan', 'Mohd_najwan', 'Najwan120_', 'NO 36, JALAN AHMAD MASLAN, 345690, SENAWANG, NEGERI SEMBILAN', 'Mohdnajwan@gmail.com'),
(204, '019-5678989', 'Faiq Syahmi', 'Faiq_syahmi', 'Faiq123_', 'NO 45, JALAN SULTAN AHMAD SHAH, 31200, IPOH, PERAK', 'FaiqSyahmi@gmail.com'),
(205, '016-3200035', 'AHMAD ALIF', 'Ahmad_alif', 'Alif205_', 'NO 47, TAMAN PENCEN, 33010, SHAH ALAM, SELANGOR', 'Ahmadalif@gmail.com'),
(206, '018-9876543', 'SITI SALEHA', 'Siti_saleha', 'Siti206_', 'NO 11, TAMAN PUCAK, 33010, SHAH ALAM, SELANGOR', 'Sitisaleha@gmail.com'),
(207, '019-7676565', 'NUR DINI', 'Nur_dini', 'Dini207_', 'NO 10, HALA LAPANGAN PERDANA, 31300, IPOH, PERAK', 'Nurdini@gmail.com'),
(220, '013-2456789', 'Fatin Farah', 'Fatin_farah', 'Fatin221_', 'N0 12, TAMAN ANCALA MAHMUD, 31230, MANJUNG, PERAK', 'Fatinfarah@gmail.com'),
(221, '012-3456666', 'Amir Muhaimin', 'Amir_muhaimin', 'Amir456_', 'NO 12, KAMPUNG KEPAYANG, 31210, TUMPAT, KELANTAN', 'AmirMuhaimin@gmail.com'),
(222, '017-4891917', 'Adneen Aiman', 'Adneen_aiman', 'Adneen191_', 'NO 13, KAMPUNG INDAH, 45670, PASIR PUTEH, KELANTAN', 'AdneenAiman@gmail.com'),
(223, '013-6667777', 'NOR AZLINA ', 'Nor_azlina', 'Azlina223_', 'NO 44, TAMAN HAMAFI, 31214, SEREMBAN, NEGERI SEMBILAN', 'Norazlina@gmail.com'),
(224, '012-32433232', 'HUSNA IZZATI', 'Husna_izzati', 'Husna131_', 'NO 226C, BANDAR SERI ASTANA, 08000, SUNGAI PETANI, KEDAH', 'husnaizzzati@gmail.com'),
(225, '013-2467892', 'MOHD IHSAN', 'Mohd_ihsan', 'Ihsan124_', 'N0 67, TAMAN ABDUL SHAH, 31211, TAMBUN, PERAK', 'MohdIhsan@gmail.com');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `PAYMENT_ID` int(11) NOT NULL,
  `AMOUNT` double NOT NULL,
  `PAYMENT_DATE` date NOT NULL,
  `PAYMENT_METHOD` varchar(20) NOT NULL,
  `BOOKING_ID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`PAYMENT_ID`, `AMOUNT`, `PAYMENT_DATE`, `PAYMENT_METHOD`, `BOOKING_ID`) VALUES
(20, 311, '2023-12-19', 'Card Credit', 1002),
(21, 326.5, '2023-12-19', 'Online Payment', 1003),
(22, 351, '2023-12-19', 'EWallet', 1004),
(23, 144, '2023-12-19', 'Card Credit', 1005),
(24, 398.5, '2023-12-19', 'Online Payment', 1006),
(25, 296, '2023-12-19', 'EWallet', 1007),
(30, 247, '2023-12-27', 'EWallet', 1010),
(31, 239.5, '2023-12-27', 'EWallet', 1011),
(32, 2058, '2023-12-27', 'Card Credit', 1012),
(33, 490.5, '2023-12-27', 'Online Payment', 1013),
(34, 319.5, '2023-12-27', 'EWallet', 1014),
(35, 443, '2023-12-27', 'EWallet', 1015),
(36, 1599, '2023-12-27', 'Card Credit', 1016),
(38, 247, '2023-12-29', 'EWallet', 1017),
(39, 678, '2023-12-30', 'Card Credit', 1018),
(40, 163.5, '2023-12-30', 'Card Credit', 1020),
(41, 287, '2024-01-01', 'EWallet', 1022),
(42, 403, '2024-01-02', 'Card Credit', 1023),
(43, 334.5, '2024-01-02', 'Online Payment', 1024),
(44, 203.5, '2024-01-03', 'Online Payment', 1025),
(45, 220, '2024-01-14', 'Online Payment', 1026),
(46, 160, '2024-01-16', 'EWallet', 1027),
(47, 210, '2024-01-16', 'EWallet', 1028),
(48, 160, '2024-01-16', 'EWallet', 1029),
(49, 144, '2024-01-16', 'EWallet', 1030),
(50, 160, '2024-01-16', 'EWallet', 1031),
(51, 126, '2024-01-16', 'EWallet', 1032),
(52, 210, '2024-01-16', 'EWallet', 1033),
(53, 216, '2024-01-16', 'Card Credit', 1034),
(54, 160, '2024-01-16', 'EWallet', 1035),
(55, 475, '2024-01-16', 'EWallet', 1036),
(56, 475, '2024-01-16', 'EWallet', 1037),
(57, 475, '2024-01-16', 'Online Payment', 1038),
(58, 1115, '2024-01-16', 'EWallet', 1039),
(59, 475, '2024-01-16', 'Card Credit', 1040),
(60, 475, '2024-01-16', 'EWallet', 1041),
(61, 475, '2024-01-16', 'Card Credit', 1042),
(62, 475, '2024-01-16', 'Online Payment', 1043),
(63, 475, '2024-01-16', 'Online Payment', 1044),
(64, 475, '2024-01-16', 'EWallet', 1045),
(65, 475, '2024-01-16', 'Card Credit', 1046),
(66, 475, '2024-01-16', 'Online Payment', 1047),
(67, 475, '2024-01-16', 'EWallet', 1048),
(68, 475, '2024-01-16', 'Card Credit', 1049),
(69, 475, '2024-01-16', 'EWallet', 1050);

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `STAFF_ID` int(11) NOT NULL,
  `IDENTIFICATION_NUMBER` char(14) NOT NULL,
  `STAFF_NAME` varchar(100) NOT NULL,
  `ADDRESS` varchar(200) NOT NULL,
  `PHONE_NUMBER` char(12) NOT NULL,
  `USERNAME` varchar(50) NOT NULL,
  `PASSWORD` varchar(12) NOT NULL,
  `EMAIL` varchar(100) NOT NULL,
  `STAFF_TYPE` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`STAFF_ID`, `IDENTIFICATION_NUMBER`, `STAFF_NAME`, `ADDRESS`, `PHONE_NUMBER`, `USERNAME`, `PASSWORD`, `EMAIL`, `STAFF_TYPE`) VALUES
(100, '030405-08-0231', 'NAFIEZ AIMAN', 'NO 31, JALAN SULTAN AZLAN SHAH, 31400, IPOH, PERAK', '011-68515178', 'nafiez_aiman', 'Nafiez100_', 'nafiezaiman@gmail.com', 'Manager'),
(101, '020103-05-0033', 'NURFARHANA AQILAH', 'NO 23, JALAN AHMAD IBRAHIM, 32560, SEMENYIH, SELANGOR', '012-3549115', 'nurfarhana_aqilah', 'Nurfarhana10', 'nurfarhanaaqilah@gmail.com', 'Manager'),
(102, '010102-03-5556', 'NURFARISHA AMNI', 'NO 32, TAMAN INDAH, 33500, JOHOR BHARU, JOHOR', '011-6951544', 'nurfarisha_amni', 'Nurfarisha10', 'nurfarishaamni@gmail.com', 'Admin'),
(103, '981211-04-7667', 'NURHANI AYUNI', 'NO 16, HALA LAPANGAN PERDANA, 31300, IPOH, PERAK', '011-5443212', 'nurhani_ayuni', 'Nurhani103', 'nurhaniayuni@gmail.com', 'Admin'),
(104, '001122-02-3333', 'MUHAMMAD AMIN', 'NO 2, TAMAN AMAN, 33200, KAMPAR, PERAK', '019-5446656', 'muhammad_amin', 'Amin104', 'muhammadamin@gmail.com', 'Normal'),
(105, '010910-07-0331', 'MUHAMMAD IZZAT', 'NO 31, KAMPUNG KERASAK, 31000, TAMBUN, PERAK', '014-1235678', 'muhammad_izzat', 'Izzat105', 'muhammadizzat@gmail.com', 'Normal'),
(106, '030310-07-0221', 'NURUL DONA', 'NO 28, TAMAN LAPAN, 34000, IPOH, PERAK', '019-44761457', 'nurul_dona', 'Dona106', 'nuruldona@gmail.com', 'Normal'),
(108, '020202-10-3333', 'Mohd Aizat', 'O 43, JALAN SAUJANA , 31230, SHAH ALAM , SELANGOR', '011-3457777', 'mohd_aizat', 'Aizat111_', 'MohdAizat@gmail.com', 'Normal'),
(109, '090909-78-3434', 'Mohd Faris', 'O 88, TAMAN RAMA, 43213, RAWANG, SELANGOR', '012-3336767', 'Mohd_faris', 'Faris112_', 'MohdFaris@gmail.com', 'Normal'),
(110, '991205-03-5667', 'MOHD MAHIRI', 'O 37, TAMAN SRI TAMAN, 31211, ALOR SETAR, KEDAH', '011-2314555', 'Mohd_mahiri', 'Mahiri110_', 'MohdMahiri@gmail.com', 'Manager'),
(111, '730129-05-1123', 'MEOR MUHAMMAD', 'O 11, JALAN TUNKU AHMAD, 34567, PARIT, PERAK', '012-3421211', 'Meor_muhammad', 'Meor111_', 'Meormuhammad@gmail.com', 'Admin'),
(112, '991213-03-5434', 'ALIEFF IRFAN', 'O 12, JALAN AHMAD SHAHRUL, 31210, TUMPAT, KELANTAN', '019-3411213', 'Alieff_irfan', 'Alieff131_', 'Alieff@gmail.com', 'Normal');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`BOOKING_ID`),
  ADD KEY `CUSTID` (`CUST_ID`),
  ADD KEY `STAFF_ID` (`STAFF_ID`,`CUST_ID`),
  ADD KEY `BOOKING_ID` (`BOOKING_ID`);

--
-- Indexes for table `booking_category`
--
ALTER TABLE `booking_category`
  ADD PRIMARY KEY (`BOOKCAT_ID`),
  ADD KEY `BOOKCAT_ID` (`BOOKCAT_ID`),
  ADD KEY `BOOKINGID` (`BOOKING_ID`),
  ADD KEY `CATEGORY_ID` (`CATEGORY_ID`);

--
-- Indexes for table `category`
--
ALTER TABLE `category`
  ADD PRIMARY KEY (`CATEGORY_ID`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`CUST_ID`),
  ADD UNIQUE KEY `CUST_PHONE` (`CUST_PHONE`),
  ADD KEY `CUST_ID` (`CUST_ID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`PAYMENT_ID`),
  ADD KEY `BOOKING_ID` (`BOOKING_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`STAFF_ID`),
  ADD UNIQUE KEY `IDENTIFICATION_NUMBER` (`IDENTIFICATION_NUMBER`),
  ADD UNIQUE KEY `PHONE_NUMBER` (`PHONE_NUMBER`),
  ADD UNIQUE KEY `USERNAME` (`USERNAME`),
  ADD UNIQUE KEY `EMAIL` (`EMAIL`),
  ADD KEY `STAFF_ID` (`STAFF_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `booking`
--
ALTER TABLE `booking`
  MODIFY `BOOKING_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1051;

--
-- AUTO_INCREMENT for table `booking_category`
--
ALTER TABLE `booking_category`
  MODIFY `BOOKCAT_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5176;

--
-- AUTO_INCREMENT for table `category`
--
ALTER TABLE `category`
  MODIFY `CATEGORY_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3006;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `CUST_ID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=226;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `PAYMENT_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=70;

--
-- AUTO_INCREMENT for table `staff`
--
ALTER TABLE `staff`
  MODIFY `STAFF_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=113;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `CUSTID` FOREIGN KEY (`CUST_ID`) REFERENCES `customer` (`CUST_ID`),
  ADD CONSTRAINT `STAFF_ID` FOREIGN KEY (`STAFF_ID`) REFERENCES `staff` (`STAFF_ID`);

--
-- Constraints for table `booking_category`
--
ALTER TABLE `booking_category`
  ADD CONSTRAINT `BOOKINGID` FOREIGN KEY (`BOOKING_ID`) REFERENCES `booking` (`BOOKING_ID`),
  ADD CONSTRAINT `CATEGORY_ID` FOREIGN KEY (`CATEGORY_ID`) REFERENCES `category` (`CATEGORY_ID`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `BOOKING_ID` FOREIGN KEY (`BOOKING_ID`) REFERENCES `booking` (`BOOKING_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
