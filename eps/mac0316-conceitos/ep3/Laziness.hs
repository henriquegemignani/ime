
module Laziness (isPrime, primes, buildList, buildTable, lcsLength) where

primes :: [Integer]
primes = 2:[ p | p <-[3,5..], isPrime p ]

testPrime :: Integer -> [Integer] -> Bool
testPrime x list
	| x < 2 = False
	| x == 2 = True
	| (mod) x (head list) == 0 = False
	| (head list) > (floor . sqrt . fromIntegral) x = True
    | otherwise = testPrime x (tail list)

isPrime :: Integer -> Bool
isPrime x = (testPrime x primes)

--------------------------

buildList :: Int -> (Int -> a) -> [a]
buildList n f = [ (f a) | a <-[0..(n - 1)]]

buildTable :: Int -> Int -> (Int -> Int -> a) -> [[a]]
buildTable n m f = [ (buildList m (f a)) | a <-[0..(n - 1)]]

lcsAux :: [[Int]] -> String -> String -> Int -> Int -> Int
lcsAux table s1 s2 i j
	| (s1 !! i) == (s2 !! j) = prev + 1
	| otherwise = max up left
	where prev = if (i > 0 && j > 0) then (table !! (i - 1) !! (j - 1)) else 0
	      up = if (i > 0) then (table !! (i - 1) !! j) else 0
	      left = if (j > 0) then (table !! i !! (j - 1)) else 0

lcsLength :: String -> String -> Int
lcsLength s1 s2 = ((table !! ((length s1) - 1)) !! ((length s2) - 1))
	where table = buildTable (length s1) (length s2) (lcsAux table s1 s2)
