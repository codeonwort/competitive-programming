-- ID:  714A (Meeting of Old Friends)
-- URL: http://codeforces.com/problemset/problem/714/A

main = do
	[l1,r1, l2,r2, k] <- (map read . words) `fmap` getLine :: IO [Integer]
	case overlap (l1,r1) (l2,r2) of
		Nothing -> print 0
		Just (left, right) ->
			if left <= k && k <= right
			then print (right - left)
			else print (right - left + 1)

overlap (l1,r1) (l2,r2)
	| r2 < l1 || r1 < l2   = Nothing
	| l1 <= l2 && r2 <= r1 = Just (l2, r2)
	| l2 <= l1 && r1 <= r2 = Just (l1, r1)
	| otherwise            = Just (max l1 l2, min r1 r2)
