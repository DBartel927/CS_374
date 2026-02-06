## What could go wrong if we didn't lock the header?

If the header were not locked, multiple processes could read the same offset
value before either one updates it. This would cause two records to be written
to the same location, corrupting the log and causing lost or overwritten data.

## What could go wrong if we didn't lock the record?

If another process or external program were reading records while a write was
in progress, it could observe a partially-written record. For example, it might
see an incomplete string or mixed data from two writes.